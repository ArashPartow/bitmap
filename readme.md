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
* Intel� C++ Compiler (9.x+)
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

                  fractal.set_pixel(x, y, jet_colormap[index]);
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
                  rgb_t colour = hsv_colormap[static_cast<int>((1000.0 * i) / max_iterations)];

                  fractal.set_pixel(x, y, colour);
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

               base      .get_pixel(sx, sy, red, green, blue);
               lens_image.set_pixel( x,  y, red, green, blue);
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

            base       .get_pixel(sx, sy, red, green, blue);
            swirl_image.set_pixel( x,  y, red, green, blue);
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
The following example will render a maze generated using a simple
recursive backtracking algorithm. The example demonstrates the use
of the drawing and colouring functionalities. Once the maze has
been completed, it will be saved to file as *'maze.bmp'*.

```c++
#include <cstdlib>
#include "bitmap_image.hpp"

enum  compass { N = 1, E = 2, S = 4, W = 8 };

const int untouched = (N | E | S | W);

struct move_t { int x, y, inverse; };

const move_t move[5] =
      {
         { 0, 0, 0 },
         // North        East         South         West
         { 0,-1, S }, { 1, 0, W }, { 0, 1, N },  {-1, 0, E }
      };

const int movemap[] = {0, 1, 2, 0, 3, 0, 0, 0, 4};

const compass perms[] =
      {
        N,S,E,W, S,N,E,W, E,N,S,W, N,E,S,W, S,E,N,W, E,S,N,W, E,S,W,N, S,E,W,N,
        W,E,S,N, E,W,S,N, S,W,E,N, W,S,E,N, W,N,E,S, N,W,E,S, E,W,N,S, W,E,N,S,
        N,E,W,S, E,N,W,S, S,N,W,E, N,S,W,E, W,S,N,E, S,W,N,E, N,W,S,E, W,N,S,E
      };

void generate_maze(int cx, int cy, response_image<int>& maze)
{
   unsigned int perm_index = 4 * ((rand() % 24));

   std::vector<compass> directions(&perms[perm_index], &perms[perm_index + 4]);

   for(std::size_t i = 0; i < directions.size(); ++i)
   {
      move_t m = move[movemap[directions[i]]];

      const int x = cx + m.x;
      const int y = cy + m.y;

      if (
           (x < 0) || (y < 0)        ||
           (untouched != maze(x,y))  ||
           (x >= (int)maze.width ()) ||
           (y >= (int)maze.height())
         )
         continue;

      maze(cx,cy) = maze(cx,cy) & ~directions[i];
      maze( x, y) = maze( x, y) & ~m.inverse;

      generate_maze(x,y, maze);
   }
}

int main()
{
   const std::size_t maze_width  = 80;
   const std::size_t maze_height = 70;

   response_image<int> maze(maze_width, maze_height);

   maze.set_all(untouched);

   generate_maze(rand() % maze_width, rand() % maze_height, maze);

   const std::size_t wall_size_x = 10; // 10 pixels
   const std::size_t wall_size_y =  8; //  8 pixels

   bitmap_image image((maze_width ) * wall_size_x, (maze_height ) * wall_size_y);
   image.clear();

   image_drawer draw(image);

   draw.pen_width(2);
   draw.pen_color(0, 255, 0);

   draw.rectangle(0, 0, image.width() - 1, image.height() - 1);

   for (std::size_t y = 0; y < maze.height(); ++y)
   {
      for (std::size_t x = 0; x < maze.width(); ++x)
      {
         const rgb_t c = prism_colormap[rand() % 1000];

         draw.pen_color(c.red, c.green, c.blue);

         // Cell(x,y) coordinates
         const int x0 = x * wall_size_x;
         const int y0 = y * wall_size_y;
         const int x1 = x * wall_size_x + wall_size_x;
         const int y1 = y * wall_size_y + wall_size_y;

         const int cell = maze(x,y);
         // Is north wall present?
         if ((cell & N))
            draw.line_segment(x0, y0, x1, y0);

         // Is south wall present?
         if ((cell & S))
            draw.line_segment(x0, y1, x1, y1);

         // Is east wall present?
         if ((cell & E))
            draw.line_segment(x1, y0, x1, y1);

         // Is west wall present?
         if ((cell & W))
            draw.line_segment(x0, y0, x0, y1);
      }
   }

   image.save_image("maze.bmp");

   return 0;
}
```

![ScreenShot](http://www.partow.net/programming/bitmap/images/maze.png?raw=true "C++ Bitmap Library Maze Generator Example - By Arash Partow")


#### Simple Example 8
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

#### Simple Example 9
The following example randomly generate circles and proceed to
inscribe multiple levels of inner equilateral triangles. The example
demonstrates the use of the cartesian canvas, pen functions, various
shape fill routines and colour maps. Once complete the rendering will
be saved to disk with the name: *'circles_and_triangles.bmp'*.

```c++
#include <cmath>
#include <cstdlib>
#include "bitmap_image.hpp"

struct point_t { double x,y; };

int main()
{
   const int canvas_width  = 700;
   const int canvas_height = 460;

   cartesian_canvas canvas(canvas_width,canvas_height);

   canvas.image().clear(255);

   canvas.pen_width(1);

   ::srand(0xA5A5A5A5);

   for (std::size_t i = 0; i < 100; ++i)
   {
      double cx = ((rand() % canvas_width ) - canvas_width  / 2.0);
      double cy = ((rand() % canvas_height) - canvas_height / 2.0);
      double r  = (rand() % 70) + 10;

      const double pi_   = 3.1415926535897932384626433832795028841971;
      const double _120d = (2.0 * pi_/ 3.0);

      double rndang = ((2.0 * pi_) / 360.0) * ((rand() % 360) + 1.0);

      point_t p0, p1, p2;
      point_t p3, p4, p5;

      p0.x = r * std::sin(1.0 * _120d + rndang) + cx;
      p0.y = r * std::cos(1.0 * _120d + rndang) + cy;
      p1.x = r * std::sin(2.0 * _120d + rndang) + cx;
      p1.y = r * std::cos(2.0 * _120d + rndang) + cy;
      p2.x = r * std::sin(3.0 * _120d + rndang) + cx;
      p2.y = r * std::cos(3.0 * _120d + rndang) + cy;

      #define rnd_colour (copper_colormap[rand() % 1000])

      // Draw and fill the circle
      canvas.pen_color(rnd_colour);
      canvas.fill_circle(cx, cy, r);
      canvas.pen_color(rnd_colour);
      canvas.circle(cx, cy, r);

      // Draw and fill the main equilateral triangles
      canvas.pen_color(rnd_colour);
      canvas.fill_triangle(p0.x,p0.y,p1.x,p1.y,p2.x,p2.y);
      canvas.pen_color(rnd_colour);
      canvas.triangle(p0.x,p0.y,p1.x,p1.y,p2.x,p2.y);

      // Draw the inner-equilateral triangles
      for (unsigned int j = 0; j < 4; ++j)
      {
         p3.x = (p0.x + p1.x) / 2.0;
         p3.y = (p0.y + p1.y) / 2.0;
         p4.x = (p1.x + p2.x) / 2.0;
         p4.y = (p1.y + p2.y) / 2.0;
         p5.x = (p2.x + p0.x) / 2.0;
         p5.y = (p2.y + p0.y) / 2.0;

         p0 = p3; p1 = p4; p2 = p5;

         canvas.pen_color(rnd_colour);
         canvas.fill_triangle(p3.x,p3.y,p4.x,p4.y,p5.x,p5.y);
         canvas.pen_color(rnd_colour);
         canvas.triangle(p3.x,p3.y,p4.x,p4.y,p5.x,p5.y);
      }
   }

   canvas.image().save_image("circles_and_triangles.bmp");

   return 0;
}
```

![ScreenShot](http://www.partow.net/programming/bitmap/images/circles_and_triangles.png?raw=true "C++ Bitmap Library Circles And Equilateral Triangles - By Arash Partow")

#### Simple Example 10
The following example renders Archimedean spirals upon a gray-scale
plasma background. The example demonstrates the use of the cartesian
canvas, pen functions, and colour maps. Once complete the rendering
will be saved to disk with the name: *'spirals.bmp'*.

```c++
#include <cmath>
#include <cstdlib>
#include "bitmap_image.hpp"

struct point_t
{
   point_t(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
   double x,y;
};

int main()
{
   const double pi_ = 3.1415926535897932384626433832795028841971;
   const double a   = 20;
   const double b   = 20;
   const double dr  = (2.0 * pi_) / 1000.0;

   const std::size_t N = 5;
   const double delta_angle = (2.0 * pi_) / N;

   std::vector<point_t> spiral;

   for (std::size_t i = 0; i < N; ++i)
   {
      spiral.push_back(
         point_t(a * std::cos((delta_angle * i)),
                 a * std::sin((delta_angle * i))));
   }

   const int canvas_width  = 600;
   const int canvas_height = 600;

   cartesian_canvas canvas(canvas_width,canvas_height);

   canvas.image().clear(0);

   {
      // Render background using Plasma effect
      double c1 = 0.9;
      double c2 = 0.5;
      double c3 = 0.3;
      double c4 = 0.7;

      bitmap_image& image = canvas.image();

      ::srand(0xA5AA5AA5);
      plasma(image,0,0,image.width(),image.height(),c1,c2,c3,c4,3.0,gray_colormap);
   }

   for (double angle = dr; (a + b * angle) < canvas.image().width() / 2; angle += dr)
   {
      for (std::size_t i = 0; i < spiral.size(); ++i)
      {
         point_t curr;

         curr.x = (a + b * angle) * std::cos(angle + delta_angle * i);
         curr.y = (a + b * angle) * std::sin(angle + delta_angle * i);

         const double centre_ratio =
            (sqrt(curr.x * curr.x + curr.y * curr.y) / (canvas.image().width() / 2.0));

              if (centre_ratio <= 0.25) canvas.pen_width(1);
         else if (centre_ratio <= 0.50) canvas.pen_width(2);
         else if (centre_ratio <= 0.75) canvas.pen_width(3);
         else if (centre_ratio <= 1.00) canvas.pen_width(4);

         unsigned int index = (unsigned int)(1000.0 * centre_ratio);

         canvas.pen_color(hsv_colormap[index]);

         canvas.line_segment(spiral[i].x,spiral[i].y, curr.x,curr.y);

         spiral[i] = curr;
      }
   }

   canvas.image().save_image("spirals.bmp");

   return 0;
}
```

![ScreenShot](http://www.partow.net/programming/bitmap/images/spirals.png?raw=true "C++ Bitmap Library Archimedean Spirals - By Arash Partow")

#### Simple Example 11
The following example will take as input *'tiger.bmp'*. The proceed
to dissect the image into 9 cells of 3x3, then proceed to randomly
shuffle cells. The example demonstrates the copying to-and-from
regions within images. Once the shuffling as been complete the
shuffled image will be saved to disk with the name: *'shuffled.bmp'*.

```c++
#include <cmath>
#include <cstdlib>
#include <vector>
#include "bitmap_image.hpp"

void shuffle(unsigned int n, std::vector<unsigned int>& v)
{
   ::srand(0x13A1515A);
   for (unsigned int i = 0; i < n; ++i) v.push_back(i);
   for (unsigned int i= v.size() - 1; i > 0; --i)
   { std::swap(v[i], v[rand() % (i + 1)]); }
}

int main()
{
   bitmap_image image("tiger.bmp");

   const unsigned int divisions    = 3;
   const unsigned int block_width  = image.width () / divisions;
   const unsigned int block_height = image.height() / divisions;

   std::vector<unsigned int> cell;

   shuffle(divisions * divisions,cell);

   bitmap_image shuffled(image.width(),image.height());
   bitmap_image region;

   shuffled.clear();

   for (std::size_t i = 0; i < cell.size(); ++i)
   {
      unsigned int x_offset = block_width  * (i % divisions);
      unsigned int y_offset = block_height * (i / divisions);

      // Copy region from original image
      image.region(x_offset, y_offset,
                   block_width, block_height, region);

      x_offset = block_width  * (cell[i] % divisions);
      y_offset = block_height * (cell[i] / divisions);

      // Paste region to new location in shuffled image
      shuffled.copy_from(region, x_offset, y_offset);
   }

   shuffled.save_image("shuffled.bmp");

   return 0;
}
```

![ScreenShot](http://www.partow.net/programming/bitmap/images/shuffled.png?raw=true "C++ Bitmap Library Image Shuffle - By Arash Partow")
