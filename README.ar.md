<div dir=rtl>

# SDL2 للغة الأسس

واجهات برمجية لمكتبة SDL2 [للغة البرمجة الأسس](https://alusus.org)، توفر وصولاً شاملاً لوظائف الرسوميات والصوتيات والإدخال في SDL2 مع دعم كامل للغة العربية.

## المزايا

- **الرسوميات**: إنشاء النوافذ، الرسم، النقوش، الأسطح، والأشكال الهندسية ثنائية الأبعاد
- **الصوتيات**: تشغيل الموسيقى والمؤثرات الصوتية عبر SDL2_mixer
- **الإدخال**: دعم لوحة المفاتيح، الفأرة، وعصا التحكم
- **تحميل الصور**: دعم صيغ PNG، JPG، TIF، وWEBP عبر SDL2_image
- **رسم النصوص**: رسم نصوص متقدم مع تكامل HarfBuzz لتشكيل النصوص العربية بشكل صحيح (Linux فقط)
- **واجهة برمجية ثنائية اللغة**: واجهات برمجية كاملة باللغة العربية إلى جانب الإنجليزية
- **متعدد المنصات**: دعم Linux وmacOS

## المكونات

توفر هذه المكتبة واجهات برمجية لـ:

- **SDL2**: الرسوميات الأساسية، النوافذ، ومعالجة الأحداث
- **SDL2_image**: تحميل ملفات الصور (PNG، JPG، WEBP، TIF)
- **SDL2_mixer**: تشغيل الصوتيات (الموسيقى والمؤثرات الصوتية)
- **SDL2_gfx**: أشكال هندسية ثنائية الأبعاد متقدمة
- **HarfBuzz Extension**: رسم نصوص مخصص مع تشكيل صحيح للنصوص العربية

## المتطلبات

### تبعيات النظام

#### Linux
```bash
sudo apt-get install libsdl2-2.0-0 libsdl2-image-2.0-0 libsdl2-mixer-2.0-0 libsdl2-gfx-1.0-0
```

#### macOS
```bash
brew install sdl2 sdl2_image sdl2_mixer sdl2_gfx
```

### الأسس
- مترجم لغة الأسس إصدار 0.8 أو أحدث
- تعليمات التثبيت متوفرة على [alusus.org](https://alusus.org)

## التثبيت

باستخدام مدير حزم الأسس (APM):

```
اشمل "مـحا"؛
مـحا.استورد_ملف("Alusus/Sdl2", "طـوب.أسس")؛
```

<div dir=ltr>

```alusus
import "Apm.alusus";
Apm.importFile("Alusus/Sdl2", "Sdl.alusus");
```

</div>

## الاستخدام

### مثال بسيط

```
اشمل "مـتم/طـرفية"؛
اشمل "مـحا"؛
مـحا.استورد_ملف("Alusus/Sdl2", "طـوب.أسس")؛

// تهيئة طوب
طـوب.هيئ(طـوب._تهيئة_مرئيات_)؛

// إنشاء نافذة
عرف نافذة: مؤشر[طـوب.نـافذة] = طـوب.نـافذة.أنشئ("لعبتي", 0, 0, 800, 600, 0)؛

// إنشاء رسام
عرف رسام: مؤشر[طـوب.رسـام] = طـوب.رسـام.أنشئ(نافذة, 1-, طـوب.رسـام.عـلامات._مسرع_)؛

// الحلقة الرئيسية
عرف مستمر: ثـنائي = صحيح؛
عرف حدث: طـوب.حـدث؛

بينما مستمر {
    // معالجة الأحداث
    بينما طـوب.استشعر_حدث(حدث~مؤشر) != 0 {
        إذا حدث.نوع == طـوب.حـدث._خروج_ {
            مستمر = خطأ؛
        }
    }

    // تنظيف الشاشة
    طـوب.رسـام.عين_لون_الرسم(رسام, 0, 0, 0, 255)؛
    طـوب.رسـام.نظف(رسام)؛

    // عرض الإطار
    طـوب.رسـام.اعرض(رسام)؛
}
```

<div=ltr>

```
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

</div>

### تحميل وعرض الصور

```
// تهيئة نظام الصور الفرعي
طـوب.صـورة.هيئ(طـوب.صـورة._تهيئة_بنج_)؛

// تحميل نقش
عرف نقش: مؤشر[طـوب.نـقش] = طـوب.صـورة.حمل_نقش(رسام, "صورة.png")؛

// رسم النقش
عرف مستطيل_الوجهة: طـوب.مـستطيل(100, 100, 200, 200)؛
طـوب.رسـام.انسخ(رسام, نقش, 0, مستطيل_الوجهة~مؤشر)؛
```

<div dir=ltr>

```
// Initialize image subsystem
Sdl.Img.init(Sdl.Img.INIT_PNG);

// Load texture
def texture: ptr[Sdl.Texture] = Sdl.Img.loadTexture(renderer, "image.png");

// Render texture
def destRect: Sdl.Rect(100, 100, 200, 200);
Sdl.Renderer.copy(renderer, texture, 0, destRect~ptr);
```

</div>

### تشغيل الصوتيات

```
// تهيئة الصوتيات
طـوب.سـمعي.هيئ(44100, طـوب.سـمعي.بـنية._مبدئي_, 2, 2048)؛

// تحميل وتشغيل موسيقى
عرف موسيقى: مؤشر[طـوب.سـمعي.مـوسيقى] = طـوب.سـمعي.حمل_موسيقى("أغنية.ogg")؛
طـوب.سـمعي.شغل(موسيقى, 1-)؛ // -1 = تكرار للأبد

// تحميل وتشغيل مؤثر صوتي
عرف صوت: مؤشر[طـوب.سـمعي.صـوت] = طـوب.سـمعي.حمل_صوت("مؤثر.wav")؛
طـوب.سـمعي.شغل(1-, صوت, 0, 1-)؛ // التشغيل على أول قناة متاحة
```

<div dir=ltr>

```
// Initialize audio
Sdl.Audio.init(44100, Sdl.Audio.Format.DEFAULT, 2, 2048);

// Load and play music
def music: ptr[Sdl.Audio.Music] = Sdl.Audio.loadMusic("song.ogg");
Sdl.Audio.play(music, -1); // -1 = loop forever

// Load and play sound effect
def sound: ptr[Sdl.Audio.Sound] = Sdl.Audio.loadWav("effect.wav");
Sdl.Audio.play(-1, sound, 0, -1); // Play on first available channel
```

</div>

### رسم النصوص (نظام لينكس فقط)

```
// تهيئة نظام الكتابة الفرعي
طـوب.كـتابة.هيئ()؛

// فتح خط
عرف خط: مؤشر[طـوب.كـتابة.خـط] = طـوب.كـتابة.افتح_خط("خط.ttf", 24)؛

// رسم نص إنجليزي
عرف لون: طـوب.لـون(255, 255, 255, 255)؛
طـوب.كـتابة.اكتب("Hello, World!", لون~مؤشر, خط, 0, 100, 100, رسام)؛

// رسم نص عربي مع تشكيل صحيح
طـوب.كـتابة.اكتب("مرحباً بالعالم", لون~مؤشر, خط, 1, 100, 100, رسام)؛
```

<div dir=ltr>

```
// Initialize text subsystem
Sdl.Text.init();

// Open font
def font: ptr[Sdl.Text.Font] = Sdl.Text.openFont("font.ttf", 24);

// Render English text
def color: Sdl.Color(255, 255, 255, 255);
Sdl.Text.renderText("Hello, World!", color~ptr, font, 0, 100, 100, renderer);

// For Arabic text with proper shaping
Sdl.Text.renderText("مرحباً بالعالم", color~ptr, font, 1, 100, 100, renderer);
```

</div>

### إدخال لوحة المفاتيح

```
// الحصول على حالة لوحة المفاتيح
عرف حالات_المفاتيح: مؤشر[مصفوفة[كلمة[8]]] = طـوب.لـوح_المفاتيح.هات_الحالة(0)؛

// فحص مفاتيح محددة
إذا حالات_المفاتيح~محتوى(طـوب.لـوح_المفاتيح.كـود_المسح.SPACE) != 0 {
    طـرفية.اطبع("تم ضغط مفتاح المسافة\ج")؛
}
```

<div dir=ltr>

```
// Get keyboard state
def keyStates: ptr[array[Word[8]]] = Sdl.Keyboard.getState(0);

// Check specific keys
if keyStates~cnt(Sdl.Keyboard.ScanCode.SPACE) != 0 {
    Console.print("Space pressed\n");
}
```

</div>

### إدخال الفأرة

```
// الحصول على حالة الفأرة
عرف س: صحيح؛
عرف ص: صحيح؛
عرف أزرار: كلمة = طـوب.فـأرة.هات_الحالة(س~مؤشر, ص~مؤشر)؛
```

<div dir=ltr>

```
// Get mouse state
def x: Int;
def y: Int;
def buttons: Word = Sdl.Mouse.getState(x~ptr, y~ptr);
```

</div>

### الرسم ثنائي الأبعاد

```
// رسم مستطيل
طـوب.رسـم.مستطيل(رسام, 100, 100, 200, 200, 0hFFFFFFFF)؛

// رسم مستطيل مليء
طـوب.رسـم.مستطيل_مليء(رسام, 50, 50, 150, 150, 0hFF0000FF)؛

// رسم دائرة (إهليج)
طـوب.رسـم.إهليج(رسام, 400, 300, 50, 50, 0h00FF00FF)؛

// رسم خط
طـوب.رسـم.خط(رسام, 0, 0, 800, 600, 5, 0hFF00FFFF)؛
```

<div dir=ltr>

```
// Draw rectangle
Sdl.Drawing.rectangle(renderer, 100, 100, 200, 200, 0xFFFFFFFF);

// Draw filled rectangle
Sdl.Drawing.filledRectangle(renderer, 50, 50, 150, 150, 0xFF0000FF);

// Draw circle (ellipse)
Sdl.Drawing.ellipse(renderer, 400, 300, 50, 50, 0x00FF00FF);

// Draw line
Sdl.Drawing.line(renderer, 0, 0, 800, 600, 5, 0xFF00FFFF);
```

</div>

## الأمثلة

يحتوي مجلد `Examples/` على برامج نموذجية:

- **مركبة.أسس** (**ship.alusus**): عرض توضيحي كامل للعبة مع رسوميات، صوتيات، رسم نصوص، وإدخال لوحة المفاتيح
- **اختبار_عصا_التحكم.أسس** (**joystick_test.alusus**): عرض توضيحي لإدخال عصا التحكم/وحدة التحكم

لتشغيل مثال:

```bash
alusus Examples/ship.alusus
```

## ملاحظات خاصة بالمنصات

### Linux
- وظائف كاملة بما في ذلك رسم النصوص باستخدام HarfBuzz
- رسم النصوص يدعم النصوص من اليسار إلى اليمين (الإنجليزية) ومن اليمين إلى اليسار (العربية)

### macOS
- الرسوميات والصوتيات والإدخال مدعومة بالكامل
- رسم النصوص باستخدام HarfBuzz معطل على macOS

## مرجع الواجهة البرمجية

### علامات التهيئة
- `طـوب._تهيئة_مرئيات_` / `Sdl.INIT_VIDEO`: تهيئة النظام الفرعي للمرئيات
- `طـوب._تهيئة_صوتيات_` / `Sdl.INIT_AUDIO`: تهيئة النظام الفرعي للصوتيات
- `طـوب._تهيئة_عصا_التحكم_` / `Sdl.INIT_JOYSTICK`: تهيئة النظام الفرعي لعصا التحكم

### أنواع الأحداث
- `طـوب.حـدث._خروج_` / `Sdl.Event.QUIT`: حدث إغلاق النافذة
- `طـوب.حـدث._زر_للأسفل_` / `Sdl.Event.KEY_DOWN`: حدث ضغط مفتاح
- `طـوب.حـدث._زر_للأعلى_` / `Sdl.Event.KEY_UP`: حدث رفع مفتاح
- `Sdl.Event.MOUSEMOTION`: حركة الفأرة
- `Sdl.Event.MOUSEBUTTONDOWN`: ضغط زر الفأرة
- `Sdl.Event.MOUSEBUTTONUP`: رفع زر الفأرة

### علامات الرسام
- `طـوب.رسـام.عـلامات._برمجي_` / `Sdl.Renderer.Flags.SOFTWARE`: رسم برمجي
- `طـوب.رسـام.عـلامات._مسرع_` / `Sdl.Renderer.Flags.ACCELERATED`: رسم مسرّع بالعتاد

### أنماط المزج
- `طـوب.نـمط_المزج._بلا_` / `Sdl.BlendMode.NONE`: بدون مزج
- `طـوب.نـمط_المزج._مزج_` / `Sdl.BlendMode.BLEND`: مزج ألفا
- `طـوب.نـمط_المزج._جمع_` / `Sdl.BlendMode.ADD`: مزج إضافي
- `طـوب.نـمط_المزج._مود_` / `Sdl.BlendMode.MOD`: مزج تعديلي

### نسق الألوان
- `طـوب.نـسق._حخزش8888_` / `Sdl.Format.RGBA8888`: نسق RGBA بـ 32 بت

### نسق الصوت
- `طـوب.سـمعي.بـنية._مبدئي_` / `Sdl.Audio.Format.DEFAULT`: النسق الافتراضي
- `طـوب.سـمعي.بـنية._ط8_` / `Sdl.Audio.Format.U8`: 8 بت بدون إشارة
- `طـوب.سـمعي.بـنية._ص16_` / `Sdl.Audio.Format.S16`: 16 بت مع إشارة

## جدول المقابلات العربية-الإنجليزية

| العربية | الإنجليزية | الوصف |
|---------|-------------|--------|
| طـوب | Sdl | الوحدة الرئيسية |
| نـافذة | Window | النافذة |
| رسـام | Renderer | الرسام |
| نـقش | Texture | النقش/الملمس |
| سـطح | Surface | السطح |
| مـستطيل | Rect | المستطيل |
| لـون | Color | اللون |
| حـدث | Event | الحدث |
| لـوح_المفاتيح | Keyboard | لوحة المفاتيح |
| فـأرة | Mouse | الفأرة |
| عـصا_التحكم | Joystick | عصا التحكم |
| صـورة | Img | الصورة |
| سـمعي | Audio | الصوتيات |
| مـوسيقى | Music | الموسيقى |
| صـوت | Sound | الصوت/المؤثر الصوتي |
| كـتابة | Text | الكتابة/النص |
| خـط | Font | الخط |
| رسـم | Drawing | الرسم |

## الترخيص

هذه المكتبة مرخصة تحت رخصة غنو العمومية الصغرى (LGPL). راجع ملفات `COPYING` و`COPYING.LESSER` للتفاصيل.

## المساهمة

المساهمات مرحب بها! يرجى تقديم المشكلات وطلبات السحب في مستودع المشروع.

## روابط

- [موقع الأسس](https://alusus.org)
- [توثيق SDL2](https://wiki.libsdl.org)
- [توثيق الأسس](https://alusus.org/documentation)

</div>

