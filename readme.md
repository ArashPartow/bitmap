#### Description
The C++ Bitmap Library consists of simple, robust, optimized and
portable processing routines for the **24-bit per pixel** bitmap
image format.


#### Capabilities
+ Read/Write 24-bit Bitmap Images
+ Pixel, row or column level batch editing
+ Color conversions (RGB,YCbCr) in byte and floating values
+ Highly optimized subsample and upsample (resizing)
+ Various color maps (1000 levels - autumn, copper, gray, hot, hsv, jet, prism, vga, yarg)
+ Texture generation (checkered pattern, plasma)
+ Graphics drawing interface (line, line-segment, rectangle, triangle, quadix, horizontal and vertical line-segments, ellipse, circle, plot pixel, pen width, pen color)
+ Cartesian canvas and associated drawing interface
+ PSNR and Image comparisons
+ Simple nearest color match from set of colors
+ Wavelength to RGB approximations
+ Single header implementation, no building required. No external dependencies


#### Download
http://www.partow.net/programming/bitmap/index.html


#### Compatibility
The C++ Bitmap Library implementation is compatible with the following C++ compilers:
* GNU Compiler Collection (4.1+)
* Intel® C++ Compiler (9.x+)
* Clang/LLVM (1.1+)
* PGI C++ (10.x+)
* Microsoft Visual Studio C++ Compiler (8.1+)
* IBM XL C/C++ (10.x+)

----

#### Simple Example 1
The following example will open a bitmap image called *'input.bmp'* and count
the number of pixels that have a red channel value of 111 and larger, then
proceed to print the count to stdout.

```c++
#include <cstdio>
#include "bitmap_image.hpp"

int main()
{
   bitmap_image image("input.bmp");

   if (!image)
   {
      printf("Error - Failed to open: input.bmp\n");
      return 1;
   }

   unsigned char red;
   unsigned char green;
   unsigned char blue;

   unsigned int total_number_of_pixels = 0;

   const unsigned int width  = image.width();
   const unsigned int height = image.height();

   for (std::size_t y = 0; y < height; ++y)
   {
      for (std::size_t x = 0; x < width; ++x)
      {
         image.get_pixel(x,y,red,green,blue);
         if (red >= 111)
            total_number_of_pixels++;
      }
   }

   printf("Number of pixels with red >= 111: %d\n",total_number_of_pixels);
   return 0;
}
```

----

#### Simple Example 2
The following example will create a bitmap of dimensions 200x200 pixels, set the
background color to orange, then proceed to draw a circle centered in the middle
of the bitmap of radius 50 pixels and of color red then a rectangle centered in
the middle of the bitmap with a width and height of 100 pixels and of color blue.
The newly constructed image will be saved to disk with the name: *'output.bmp'*.

```c++
#include "bitmap_image.hpp"

int main()
{
   bitmap_image image(200,200);

   // set background to orange
   image.set_all_channels(255,150,50);

   image_drawer draw(image);

   draw.pen_width(3);
   draw.pen_color(255,0,0);
   draw.circle(image.width() / 2, image.height() / 2,50);

   draw.pen_width(1);
   draw.pen_color(0,0,255);
   draw.rectangle(50,50,150,150);

   image.save_image("output.bmp");

   return 0
}
```

----

#### Simple Example 3
The following example will render the Mandelbrot set fractal and save
the generated bitmap as *'mandelbrot_set.bmp'*.

```c++
#include <cmath>
#include "bitmap_image.hpp"

int main()
{
   bitmap_image fractal(600,400);

   fractal.clear();

   double    cr,    ci;
   double nextr, nexti;
   double prevr, previ;

   const unsigned int max_iterations = 1000;

   for (unsigned int y = 0; y < fractal.height(); ++y)
   {
      for (unsigned int x = 0; x < fractal.width(); ++x)
      {
         cr = 1.5 * (2.0 * x / fractal.width () - 1.0) - 0.5;
         ci =       (2.0 * y / fractal.height() - 1.0);

         nextr = nexti = 0;
         prevr = previ = 0;

         for (unsigned int i = 0; i < max_iterations; i++)
         {
            prevr = nextr;
            previ = nexti;

            nextr =     prevr * prevr - previ * previ + cr;
            nexti = 2 * prevr * previ + ci;

            if (((nextr * nextr) + (nexti * nexti)) > 4)
            {
               if (max_iterations != i)
               {
                  using namespace std;

                  double z = sqrt(nextr * nextr + nexti * nexti);

                  //https://en.wikipedia.org/wiki/Mandelbrot_set#Continuous_.28smooth.29_coloring
                  unsigned int index = static_cast<unsigned int>
                     (1000.0 * log2(1.75 + i - log2(log2(z))) / log2(max_iterations));

                  rgb_store c = jet_colormap[index];

                  fractal.set_pixel(x, y, c.red, c.green, c.blue);
               }

               break;
            }
         }
      }
   }

   fractal.save_image("mandelbrot_set.bmp");

   return 0;
}
```

![ScreenShot](http://www.partow.net/programming/bitmap/images/mandelbrot_set.png?raw=true "C++ Bitmap Library Mandelbrot Set Fractal - By Arash Partow")

----

#### Simple Example 4
The following example will render the Julia set fractal and save the
generated bitmap as *'julia_set.bmp'*.

```c++
#include <cmath>
#include "bitmap_image.hpp"

int main()
{
   bitmap_image fractal(600,400);

   fractal.clear();

   const unsigned int max_iterations = 300;

   const double cr = -0.70000;
   const double ci =  0.27015;

   double prevr, previ;

   for (unsigned int y = 0; y < fractal.height(); ++y)
   {
      for (unsigned int x = 0; x < fractal.width(); ++x)
      {
         double nextr = 1.5 * (2.0 * x / fractal.width () - 1.0);
         double nexti =       (2.0 * y / fractal.height() - 1.0);

         for (unsigned int i = 0; i < max_iterations; i++)
         {
            prevr = nextr;
            previ = nexti;

            nextr =     prevr * prevr - previ * previ + cr;
            nexti = 2 * prevr * previ + ci;

            if (((nextr * nextr) + (nexti * nexti)) > 4)
            {
               if (max_iterations != i)
               {
                  rgb_store c = hsv_colormap[static_cast<int>((1000.0 * i) / max_iterations)];

                  fractal.set_pixel(x, y, c.red, c.green, c.blue);
               }

               break;
            }
         }
      }
   }

   fractal.save_image("julia_set.bmp");

   return 0;
}
```

![ScreenShot](http://www.partow.net/programming/bitmap/images/julia_set.png?raw=true "C++ Bitmap Library Julia Set Fractal - By Arash Partow")

#### Simple Example 5
The following example will render a baseline image using a combination of plasma
and checkered pattern effects. Then proceed to apply a lens distortion upon the
base image. Finally both the base and the lens distorted versions of the images
will be saved to file as *'base.bmp'* and *'lens_effect.bmp'* respectively.

```c++
#include <algorithm>
#include <cmath>
#include "bitmap_image.hpp"

int main()
{
   bitmap_image base(600,600);

   base.clear();

   {
      const double c1 = 0.8;
      const double c2 = 0.4;
      const double c3 = 0.2;
      const double c4 = 0.6;

      ::srand(0xA5AA5AA5);
      plasma(base,0,0,base.width(),base.height(),c1,c2,c3,c4,3.0,jet_colormap);
      checkered_pattern(30,30,230,bitmap_image::  red_plane,base);
      checkered_pattern(30,30,  0,bitmap_image::green_plane,base);
      checkered_pattern(30,30,100,bitmap_image:: blue_plane,base);
   }

   bitmap_image lens_image(base.width(),base.height());

   lens_image = base;

   double lens_center_x = base.width () / 2;
   double lens_center_y = base.height() / 2;
   double lens_radius   = std::min(base.width(), base.height()) / 4;
   double lens_factor   = 0.7;

   for (unsigned int x = 0; x < base.width(); x++)
   {
      for (unsigned int y = 0; y < base.height(); y++)
      {
         double dx = x - lens_center_x;
         double dy = y - lens_center_y;

         double distance = std::sqrt((dx * dx) + (dy * dy));

         if (distance <= lens_radius)
         {
            double radius     = distance / lens_radius;
            double angle      = std::atan2(dy, dx);
            double distortion = std::pow(radius, lens_factor) * distance;

            int sx = static_cast<int>(distortion * std::cos(angle) + lens_center_x);
            int sy = static_cast<int>(distortion * std::sin(angle) + lens_center_y);

            if (
                 (sx >= 0)                 &&
                 (sy >= 0)                 &&
                 (sx < (int)base.width ()) &&
                 (sy < (int)base.height())
               )
            {
               unsigned char   red;
               unsigned char green;
               unsigned char  blue;

               base      .get_pixel(sx,sy,red,green,blue);
               lens_image.set_pixel( x, y,red,green,blue);
            }
         }
      }
   }

   base      .save_image("base.bmp"       );
   lens_image.save_image("lens_effect.bmp");

   return 0;
}
```

![ScreenShot](http://www.partow.net/programming/bitmap/images/lens_effect.png?raw=true "C++ Bitmap Library Magnifying Lens Effect Example - By Arash Partow")

#### Simple Example 6
The following example will render a baseline image using a combination
of plasma and checkered pattern effects. Then proceed to apply a swirl
distortion upon the base image. Finally both the base and the swirl
distorted versions of the images will be saved to file as *'base.bmp'*
and *'swirl_effect.bmp'* respectively.

```c++
#include <algorithm>
#include <cmath>
#include "bitmap_image.hpp"

int main()
{
   bitmap_image base(600,600);

   base.clear();

   {
      const double c1 = 0.8;
      const double c2 = 0.4;
      const double c3 = 0.2;
      const double c4 = 0.6;

      ::srand(0x5A5A5A5A);
      plasma(base,0,0,base.width(),base.height(),c1,c2,c3,c4,7.0,jet_colormap);
      checkered_pattern(20,20,250,bitmap_image::  red_plane,base);
      checkered_pattern(20,20, 10,bitmap_image::green_plane,base);
      checkered_pattern(20,20, 10,bitmap_image:: blue_plane,base);
   }

   bitmap_image swirl_image(base.width(),base.height());

   swirl_image.clear();

   double swirl_center_x = base.width () / 2;
   double swirl_center_y = base.height() / 2;
   double swirl_radius   = std::min(base.width(), base.height()) / 3;

   const double pi_ = 3.1415926535897932384626433832795028841971;
   const double swirl_angle = pi_ / 3.0;

   for (unsigned int x = 0; x < base.width(); x++)
   {
      for (unsigned int y = 0; y < base.height(); y++)
      {
         double dx = x - swirl_center_x;
         double dy = y - swirl_center_y;

         double distance = std::sqrt((dx * dx) + (dy * dy));

         double angle = swirl_angle * (distance / swirl_radius);

         const double cosa = std::cos(angle);
         const double sina = std::sin(angle);

         int sx = static_cast<int>(dx * cosa - dy * sina + swirl_center_x);
         int sy = static_cast<int>(dx * sina + dy * cosa + swirl_center_y);

         if (
              (sx >= 0)                 &&
              (sy >= 0)                 &&
              (sx < (int)base.width ()) &&
              (sy < (int)base.height())
            )
         {
            unsigned char   red;
            unsigned char green;
            unsigned char  blue;

            base       .get_pixel(sx,sy,red,green,blue);
            swirl_image.set_pixel( x, y,red,green,blue);
         }
      }
   }

   base       .save_image("base.bmp"        );
   swirl_image.save_image("swirl_effect.bmp");

   return 0;
}
```

![ScreenShot](http://www.partow.net/programming/bitmap/images/swirl_effect.png?raw=true "C++ Bitmap Library Swirl Effect Example - By Arash Partow")

#### Simple Example 7
The following example will render a group of fireballs placed
equidistant to their immediate neighbours following a Lissajous curve.
The fireballs will then proceed move within the plane using the curve
as their path. The example demonstrates the construction of a
piecewise colour palette and the response_image functionality. After
having 'simulated' N-frames, the final frame will be converted to a
bitmap and then saved to file as *'fireballs.bmp'*.

```c++
#include <cmath>
#include <iterator>
#include <vector>
#include "bitmap_image.hpp"

struct lissajous_curve
{
   lissajous_curve(const double xs, const double ys)
   : scale_x(xs),
     scale_y(ys)
   {}

   inline double x(const double t) const { return scale_x * std::sin(    t); }
   inline double y(const double t) const { return scale_y * std::cos(3 * t); }

   double scale_x;
   double scale_y;
};

int main()
{
   bitmap_image image(600,400);

   image.clear();

   lissajous_curve curve(image.width () / 2.0 - 25, image.height() / 2.0 - 25);

   const double pi_   = 3.1415926535897932384626433832795028841971;
   const double delta = (2.0 * pi_) / 100000.0;

   const std::size_t max_fire_balls   = 30;
   const std::size_t number_of_frames = 3000;

   const double cooling_factor = 0.940; // [0,1]

   // Arc-length of curve: x(t) = a0 * sin(4t), y(t) = a1 * cos(3t)
   const double curve_length = 5102.0;

   double segment_length  = curve_length / max_fire_balls;
   double curr_seg_length = 0;

   double prev_x = curve.x(0);
   double prev_y = curve.y(0);

   std::vector<double> fire_ball;

   // Set the initial location for each fireball
   for (double t = delta;  fire_ball.size() < max_fire_balls; t += delta)
   {
      double center_x = curve.x(t);
      double center_y = curve.y(t);

      double dx = (prev_x - center_x);
      double dy = (prev_y - center_y);

      curr_seg_length += std::sqrt((dx * dx) + (dy * dy));

      prev_x = center_x;
      prev_y = center_y;

      if (curr_seg_length >= segment_length)
      {
         curr_seg_length = 0.0;
         fire_ball.push_back(t);
      }
   }

   response_image<double> resp_image(image.width(),image.height(), -1.0);
   response_image<double> fb_misses (image.width(),image.height(), -1.0);

   resp_image.set_all(-999.0);
   fb_misses .set_all(   0.0);

   std::vector<rgb_t> fire_palette;

   // Baseline colours used fire palette
   rgb_t black  = make_colour(0,    0,  0);
   rgb_t red    = make_colour(255,  0,  0);
   rgb_t yellow = make_colour(255,255,  0);
   rgb_t white  = make_colour(255,255,255);

   // Setup the fire palette:
   // Black (Coolest - 0) --> Red --> Yellow --> White (Hottest - 999)
   generate_colours(334, black,    red, std::back_inserter(fire_palette));
   generate_colours(333,   red, yellow, std::back_inserter(fire_palette));
   generate_colours(333,yellow,  white, std::back_inserter(fire_palette));

   for (std::size_t k = 0; k < number_of_frames; ++k)
   {
      fb_misses.inc_all(1);

      // Render fireballs on response image
      for (std::size_t i = 0; i < fire_ball.size(); ++i)
      {
         double fb_x = curve.x(fire_ball[i]) + image.width () / 2.0;
         double fb_y = curve.y(fire_ball[i]) + image.height() / 2.0;

         // Draw circles with radii in the range [1,10]
         for (double t = 0;  t < (2 * pi_); t += (((2.0 * pi_) / 360)))
         {
            for (double r = 1; r <= 10; ++r)
            {
               std::size_t rx = static_cast<std::size_t>(r * std::sin(t) + fb_x);
               std::size_t ry = static_cast<std::size_t>(r * std::cos(t) + fb_y);

               double heat_distortion = 50.0 * std::cos(delta * i) + 50; // per-frame in [0,100]

               resp_image(rx,ry) = fire_palette.size() * 0.8 + heat_distortion + (::rand() % 100);
               fb_misses (rx,ry) = 0;
            }
         }

         // Move fireball to its next location
         fire_ball[i] += delta;
      }

      // Apply cooling process to the entire plane
      for (std::size_t y = 1; y < resp_image.height() - 1; ++y)
      {
         for (std::size_t x = 1; x < resp_image.width() - 1; ++x)
         {
            double avg = (
                           resp_image(x - 1, y - 1) + resp_image(x    , y - 1) +
                           resp_image(x + 1, y - 1) + resp_image(x - 1, y    ) +
                           resp_image(x + 1, y    ) + resp_image(x    , y + 1) +
                           resp_image(x - 1, y + 1) + resp_image(x + 1, y + 1)
                         ) / (7.0 + cooling_factor);

            // Only allow cooler averages to be applied
            if (avg > resp_image(x, y))
               continue;

            // More rapidly cool points that haven't seen fireballs in the last N-frames
            if (fb_misses(x,y) > 2000)
               avg *= 0.90 + ((::rand() % 10) / 100.0);

            // Clamp average in the range [0,999]
            resp_image(x,y) = ((avg < 0.0) ? 0.0 : ((avg > 999.0) ? 999.0 : avg));
         }
      }
   }

   convert_rsp_to_image(resp_image,fire_palette,image);

   image.save_image("fireballs.bmp");

   return 0;
}
```

![ScreenShot](http://www.partow.net/programming/bitmap/images/fireballs.png?raw=true "C++ Bitmap Library Fire Balls Example - By Arash Partow")
