#### Description
The C++ Bitmap Library consists of simple, robust, optimized and portable processing routines for the **24-bit per pixel** bitmap image format.


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
The following example will open a bitmap image called *'input.bmp'* and count the
number of pixels that have a red channel value of 111 and larger, then proceed
to print the count to stdout.

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
The following example will render the Mandelbrot set fractal and save the generated bitmap as *'mandelbrot_set.bmp'*.

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
The following example will render a baseline image using a combination of plasma and
checkered pattern effects. Then proceed to apply a swirl distortion upon the base image.
Finally both the base and the swirl distorted versions of the images will be saved to
file as *'base.bmp'* and *'swirl_effect.bmp'* respectively.

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
