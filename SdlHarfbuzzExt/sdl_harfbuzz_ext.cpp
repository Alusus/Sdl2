#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <harfbuzz/hb.h>
#include <harfbuzz/hb-ft.h>

struct Font {
	FT_Face face;
	hb_font_t* hb_font;
};

FT_Library ftLibrary;


extern "C" void sdlhbext_init()
{
	FT_Init_FreeType(&ftLibrary);
}


extern "C" void sdlhbext_destroy()
{
	FT_Done_FreeType(ftLibrary);
}


extern "C" Font* sdlhbext_openFont(char const *path, int size)
{
  Font *font = new Font;
	FT_New_Face(ftLibrary, path, 0, &font->face);
	FT_Set_Pixel_Sizes(font->face, 0, size);

	font->hb_font = hb_ft_font_create(font->face, 0);
  return font;
}


extern "C" void sdlhbext_releaseFont(Font *font)
{
	hb_font_destroy(font->hb_font);
	FT_Done_Face(font->face);
  delete font;
}


SDL_Texture* createTextureFromFtBitmap(SDL_Renderer* renderer, const FT_Bitmap& bitmap, const SDL_Color& color)
{
	SDL_Texture* output = SDL_CreateTexture(
    renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING,
		bitmap.width,
		bitmap.rows
  );

	void *buffer;
	int pitch;
	SDL_LockTexture(output, NULL, &buffer, &pitch);

	unsigned char *src_pixels = bitmap.buffer;
	unsigned int *target_pixels = reinterpret_cast<unsigned int*>(buffer);

	SDL_PixelFormat* pixel_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

	for (int y = 0; y < bitmap.rows; y++)
	{
		for (int x = 0; x < bitmap.width; x++)
		{
			int index = (y * bitmap.width) + x;

			unsigned int alpha = src_pixels[index];
			unsigned int pixel_value =
				SDL_MapRGBA(pixel_format, color.r, color.g, color.b, alpha);

			target_pixels[index] = pixel_value;
		}
	}

	SDL_FreeFormat(pixel_format);
	SDL_UnlockTexture(output);

	return output;
}


void calculateSurfaceBound(
  hb_glyph_info_t *glyph_infos, hb_glyph_position_t *glyph_positions, const unsigned int& glyph_count,
  const FT_Face& face, SDL_Rect& rect, const FT_Int32& flags = FT_LOAD_DEFAULT
) {
	int width = 0;
	int above_base_line = 0;
	int below_base_line = 0;

	for (unsigned int i = 0; i < glyph_count; i++)
	{
		FT_Load_Glyph(face, glyph_infos[i].codepoint, FT_LOAD_DEFAULT | flags);
		width += (glyph_positions[i].x_advance >> 6);
		int bearing =
			(face->glyph->metrics.horiBearingY >> 6) + (glyph_positions[i].y_offset >> 6);

		if (bearing > above_base_line)
			above_base_line = bearing;

		int height_minus_bearing = (face->glyph->metrics.height >> 6) - bearing;
		if (height_minus_bearing > below_base_line)
			below_base_line = height_minus_bearing;
	}

	rect.x = 0;
	rect.y = -above_base_line;
	rect.w = width;
	rect.h = above_base_line + below_base_line;

}


extern "C" void sdlhbext_calculateSize(
  char const *text, Font *font, int arabic, SDL_Rect &rect
) {
	hb_buffer_t *buffer = hb_buffer_create();

  if (arabic) {
    hb_buffer_set_direction(buffer, HB_DIRECTION_RTL);
    hb_buffer_set_script(buffer, HB_SCRIPT_ARABIC);
  } else {
    hb_buffer_set_direction(buffer, HB_DIRECTION_LTR);
    hb_buffer_set_script(buffer, HB_SCRIPT_LATIN);
  }

  int len = strlen(text);
	hb_buffer_add_utf8(buffer, text, len, 0, len);

	hb_shape(font->hb_font, buffer, NULL, 0);

	unsigned int glyph_count = hb_buffer_get_length(buffer);
	hb_glyph_info_t *glyph_infos = hb_buffer_get_glyph_infos(buffer, NULL);
	hb_glyph_position_t *glyph_positions = hb_buffer_get_glyph_positions(buffer, NULL);

	calculateSurfaceBound(
    glyph_infos,
		glyph_positions,
		glyph_count,
		font->face,
		rect,
		FT_LOAD_DEFAULT
  );

	hb_buffer_destroy(buffer);
}


extern "C" void sdlhbext_render(
  char const *text, SDL_Color *color, Font *font, int arabic, SDL_Renderer *renderer
) {
	hb_buffer_t *buffer = hb_buffer_create();

  if (arabic) {
    hb_buffer_set_direction(buffer, HB_DIRECTION_RTL);
    hb_buffer_set_script(buffer, HB_SCRIPT_ARABIC);
  } else {
    hb_buffer_set_direction(buffer, HB_DIRECTION_LTR);
    hb_buffer_set_script(buffer, HB_SCRIPT_LATIN);
  }

  int len = strlen(text);
	hb_buffer_add_utf8(buffer, text, len, 0, len);

	hb_shape(font->hb_font, buffer, NULL, 0);

	unsigned int glyph_count = hb_buffer_get_length(buffer);
	hb_glyph_info_t *glyph_infos = hb_buffer_get_glyph_infos(buffer, NULL);
	hb_glyph_position_t *glyph_positions = hb_buffer_get_glyph_positions(buffer, NULL);

  SDL_Rect rect;

	calculateSurfaceBound(
    glyph_infos,
		glyph_positions,
		glyph_count,
		font->face,
		rect,
		FT_LOAD_DEFAULT
  );

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	int baseline = -rect.y;
	int x = 0;

	for (unsigned int i = 0; i < glyph_count; i++)
	{
		FT_Load_Glyph( font->face,
			glyph_infos[i].codepoint,
			FT_LOAD_RENDER | FT_LOAD_DEFAULT);

		SDL_Texture* glyph_texture = createTextureFromFtBitmap(renderer, font->face->glyph->bitmap, *color);
  	SDL_SetTextureBlendMode(glyph_texture, SDL_BLENDMODE_BLEND);

		SDL_Rect dest;
		SDL_QueryTexture(glyph_texture, NULL, NULL, &dest.w, &dest.h);
		dest.x = x + (font->face->glyph->metrics.horiBearingX >> 6) + (glyph_positions[i].x_offset >> 6);
		dest.y = baseline - (font->face->glyph->metrics.horiBearingY >> 6) - (glyph_positions[i].y_offset >> 6);


		SDL_RenderCopy(renderer, glyph_texture, NULL, &dest);

		x += (glyph_positions[i].x_advance >> 6);

		SDL_DestroyTexture(glyph_texture);
	}

	hb_buffer_destroy(buffer);
}


extern "C" SDL_Texture* sdlhbext_createTexture(
  char const *text, SDL_Color *color, Font *font, int arabic, SDL_Renderer *renderer
) {
	hb_buffer_t *buffer = hb_buffer_create();

  if (arabic) {
    hb_buffer_set_direction(buffer, HB_DIRECTION_RTL);
    hb_buffer_set_script(buffer, HB_SCRIPT_ARABIC);
  } else {
    hb_buffer_set_direction(buffer, HB_DIRECTION_LTR);
    hb_buffer_set_script(buffer, HB_SCRIPT_LATIN);
  }

  int len = strlen(text);
	hb_buffer_add_utf8(buffer, text, len, 0, len);

	hb_shape(font->hb_font, buffer, NULL, 0);

	unsigned int glyph_count = hb_buffer_get_length(buffer);
	hb_glyph_info_t *glyph_infos = hb_buffer_get_glyph_infos(buffer, NULL);
	hb_glyph_position_t *glyph_positions = hb_buffer_get_glyph_positions(buffer, NULL);

  SDL_Rect rect;

	calculateSurfaceBound(
    glyph_infos,
		glyph_positions,
		glyph_count,
		font->face,
		rect,
		FT_LOAD_DEFAULT
  );

	SDL_Texture *target = SDL_CreateTexture(
    renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_TARGET,
		rect.w,
		rect.h
  );

	SDL_SetTextureBlendMode(target, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, target);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, NULL);

	int baseline = -rect.y;
	int x = 0;

	for (unsigned int i = 0; i < glyph_count; i++)
	{
		FT_Load_Glyph( font->face,
			glyph_infos[i].codepoint,
			FT_LOAD_RENDER | FT_LOAD_DEFAULT);

		SDL_Texture* glyph_texture = createTextureFromFtBitmap(renderer, font->face->glyph->bitmap, *color);
  	SDL_SetTextureBlendMode(glyph_texture, SDL_BLENDMODE_BLEND);

		SDL_Rect dest;
		SDL_QueryTexture(glyph_texture, NULL, NULL, &dest.w, &dest.h);
		dest.x = x + (font->face->glyph->metrics.horiBearingX >> 6) + (glyph_positions[i].x_offset >> 6);
		dest.y = baseline - (font->face->glyph->metrics.horiBearingY >> 6) - (glyph_positions[i].y_offset >> 6);


		SDL_RenderCopy(renderer, glyph_texture, NULL, &dest);

		x += (glyph_positions[i].x_advance >> 6);

		SDL_DestroyTexture(glyph_texture);
	}

	hb_buffer_destroy(buffer);

	SDL_SetRenderTarget(renderer, NULL);

  return target;
}
