# SDL2 for Alusus
[[العربية]](README.ar.md)

SDL2 bindings for the [Alusus Programming Language](https://alusus.org), providing comprehensive access to SDL2 graphics, audio, and input functionality with full Arabic language support.

## Features

- **Graphics**: Window creation, rendering, textures, surfaces, and 2D drawing primitives
- **Audio**: Music playback and sound effects via SDL2_mixer
- **Input**: Keyboard, mouse, and joystick/gamepad support
- **Image Loading**: PNG, JPG, TIF, and WEBP format support via SDL2_image
- **Text Rendering**: Advanced text rendering with HarfBuzz integration for proper Arabic text shaping (Linux only)
- **Bilingual API**: Full Arabic language bindings alongside English API
- **Cross-Platform**: Support for Linux and macOS

## Components

This library provides bindings for:

- **SDL2**: Core graphics, windowing, and event handling
- **SDL2_image**: Image file loading (PNG, JPG, WEBP, TIF)
- **SDL2_mixer**: Audio playback (music and sound effects)
- **SDL2_gfx**: Advanced 2D drawing primitives
- **HarfBuzz Extension**: Custom text rendering with proper Arabic text shaping

## Requirements

### System Dependencies

#### Linux
```bash
sudo apt-get install libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-gfx-1.0-0
```

#### macOS
```bash
brew install sdl2 sdl2_image sdl2_mixer sdl2_gfx
```

### Alusus
- Alusus compiler version 0.8 or later
- Installation instructions available at [alusus.org](https://alusus.org)

## Installation

Using Alusus Package Manager (APM):

```alusus
import "Apm.alusus";
Apm.importFile("Alusus/Sdl2", "Sdl.alusus");
```

## Usage

### Basic Example (English)

```alusus
import "Srl/Console.alusus";
import "Apm.alusus";
Apm.importFile("Alusus/Sdl2", "Sdl.alusus");

// Initialize SDL
Sdl.init(Sdl.INIT_VIDEO);

// Create window
def window: ptr[Sdl.Window] = Sdl.Window.create("My Game", 0, 0, 800, 600, 0);

// Create renderer
def renderer: ptr[Sdl.Renderer] = Sdl.Renderer.create(window, -1, Sdl.Renderer.Flags.ACCELERATED);

// Main loop
def running: Bool = true;
def event: Sdl.Event;

while running {
    // Handle events
    while Sdl.pollEvent(event~ptr) != 0 {
        if event.eventType == Sdl.Event.QUIT {
            running = false;
        }
    }

    // Clear screen
    Sdl.Renderer.setDrawColor(renderer, 0, 0, 0, 255);
    Sdl.Renderer.clear(renderer);

    // Present frame
    Sdl.Renderer.present(renderer);
}
```

### Loading and Displaying Images

```alusus
// Initialize image subsystem
Sdl.Img.init(Sdl.Img.INIT_PNG);

// Load texture
def texture: ptr[Sdl.Texture] = Sdl.Img.loadTexture(renderer, "image.png");

// Render texture
def destRect: Sdl.Rect(100, 100, 200, 200);
Sdl.Renderer.copy(renderer, texture, 0, destRect~ptr);
```

### Playing Audio

```alusus
// Initialize audio
Sdl.Audio.init(44100, Sdl.Audio.Format.DEFAULT, 2, 2048);

// Load and play music
def music: ptr[Sdl.Audio.Music] = Sdl.Audio.loadMusic("song.ogg");
Sdl.Audio.play(music, -1); // -1 = loop forever

// Load and play sound effect
def sound: ptr[Sdl.Audio.Sound] = Sdl.Audio.loadWav("effect.wav");
Sdl.Audio.play(-1, sound, 0, -1); // Play on first available channel
```

### Text Rendering (Linux only)

```alusus
// Initialize text subsystem
Sdl.Text.init();

// Open font
def font: ptr[Sdl.Text.Font] = Sdl.Text.openFont("font.ttf", 24);

// Render text
def color: Sdl.Color(255, 255, 255, 255);
Sdl.Text.renderText("Hello, World!", color~ptr, font, 0, 100, 100, renderer);

// For Arabic text with proper shaping
Sdl.Text.renderText("مرحبا بالعالم", color~ptr, font, 1, 100, 100, renderer);
```

### Keyboard Input

```alusus
// Get keyboard state
def keyStates: ptr[array[Word[8]]] = Sdl.Keyboard.getState(0);

// Check specific keys
if keyStates~cnt(Sdl.Keyboard.ScanCode.SPACE) != 0 {
    Console.print("Space pressed\n");
}
```

### Mouse Input

```alusus
// Get mouse state
def x: Int;
def y: Int;
def buttons: Word = Sdl.Mouse.getState(x~ptr, y~ptr);
```

## Examples

The `Examples/` directory contains sample programs:

- **ship.alusus**: Complete game demo with graphics, audio, text rendering, and keyboard input
- **joystick_test.alusus**: Joystick/gamepad input demonstration

To run an example:

```bash
alusus Examples/ship.alusus
```

## Platform-Specific Notes

### Linux
- Full functionality including HarfBuzz text rendering
- Text rendering supports both LTR (English) and RTL (Arabic) scripts

### macOS
- Graphics, audio, and input fully supported
- HarfBuzz text rendering is disabled on macOS

## API Reference

### Initialization Flags
- `Sdl.INIT_VIDEO`: Initialize video subsystem
- `Sdl.INIT_AUDIO`: Initialize audio subsystem
- `Sdl.INIT_JOYSTICK`: Initialize joystick subsystem

### Event Types
- `Sdl.Event.QUIT`: Window close event
- `Sdl.Event.KEY_DOWN`: Key press event
- `Sdl.Event.KEY_UP`: Key release event
- `Sdl.Event.MOUSEMOTION`: Mouse movement
- `Sdl.Event.MOUSEBUTTONDOWN`: Mouse button press
- `Sdl.Event.MOUSEBUTTONUP`: Mouse button release

### Renderer Flags
- `Sdl.Renderer.Flags.SOFTWARE`: Software rendering
- `Sdl.Renderer.Flags.ACCELERATED`: Hardware-accelerated rendering

### Blend Modes
- `Sdl.BlendMode.NONE`: No blending
- `Sdl.BlendMode.BLEND`: Alpha blending
- `Sdl.BlendMode.ADD`: Additive blending
- `Sdl.BlendMode.MOD`: Modulative blending

## License

This library is licensed under the GNU Lesser General Public License (LGPL). See the `COPYING` and `COPYING.LESSER` files for details.

## Contributing

Contributions are welcome! Please submit issues and pull requests on the project repository.

## Links

- [Alusus Website](https://alusus.org)
- [SDL2 Documentation](https://wiki.libsdl.org)
- [Alusus Documentation](https://alusus.org/documentation)

