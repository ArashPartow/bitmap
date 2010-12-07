/*
 ***************************************************************************
 *                                                                         *
 *                         Platform Independent                            *
 *                   Bitmap Image Reader Writer Library                    *
 *                                                                         *
 * Author: Arash Partow - 2002                                             *
 * URL: http://www.partow.net                                              *
 *                                                                         *
 * Copyright notice:                                                       *
 * Free use of the Platform Independent Bitmap Image Reader Writer Library *
 * is permitted under the guidelines and in accordance with the most       *
 * current version of the Common Public License.                           *
 * http://www.opensource.org/licenses/cpl1.0.php                           *
 *                                                                         *
 ***************************************************************************
*/

#include <iostream>
#include <string>
#include <cstdlib>

#include "bitmap_image.hpp"

inline void test01()
{
   std::string file_name = "image.bmp";
   bitmap_image image("image.bmp");
   image.save_image("saved.bmp");
}

inline void test02()
{
   std::string file_name = "image.bmp";
   bitmap_image image("image.bmp");
   image.save_image("saved.bmp");

   image.vertical_flip();
   image.save_image("saved_vert_flip.bmp");
   image.vertical_flip();

   image.horizontal_flip();
   image.save_image("saved_horiz_flip.bmp");
}

inline void test03()
{
   std::string file_name = "image.bmp";
   bitmap_image image("image.bmp");
   bitmap_image subsampled_image1;
   bitmap_image subsampled_image2;
   bitmap_image subsampled_image3;

   image.subsample(subsampled_image1);
   subsampled_image1.save_image("1xsubsampled_image.bmp");

   subsampled_image1.subsample(subsampled_image2);
   subsampled_image2.save_image("2xsubsampled_image.bmp");

   subsampled_image2.subsample(subsampled_image3);
   subsampled_image3.save_image("3xsubsampled_image.bmp");
}

inline void test04()
{
   std::string file_name = "image.bmp";
   bitmap_image image("image.bmp");

   bitmap_image upsampled_image1;
   bitmap_image upsampled_image2;
   bitmap_image upsampled_image3;

   image.upsample(upsampled_image1);
   upsampled_image1.save_image("1xupsampled_image.bmp");

   upsampled_image1.upsample(upsampled_image2);
   upsampled_image2.save_image("2xupsampled_image.bmp");

   upsampled_image2.upsample(upsampled_image3);
   upsampled_image3.save_image("3xupsampled_image.bmp");
}

inline void test05()
{
   std::string file_name = "image.bmp";
   bitmap_image image("image.bmp");
   image.set_all_ith_bits_low(0);
   image.save_image("lsb0_removed_saved.bmp");
   image.set_all_ith_bits_low(1);
   image.save_image("lsb01_removed_saved.bmp");
   image.set_all_ith_bits_low(2);
   image.save_image("lsb012_removed_saved.bmp");
   image.set_all_ith_bits_low(3);
   image.save_image("lsb0123_removed_saved.bmp");
   image.set_all_ith_bits_low(4);
   image.save_image("lsb01234_removed_saved.bmp");
   image.set_all_ith_bits_low(5);
   image.save_image("lsb012345_removed_saved.bmp");
   image.set_all_ith_bits_low(6);
   image.save_image("lsb0123456_removed_saved.bmp");
}

inline void test06()
{
   std::string file_name = "image.bmp";
   bitmap_image image("image.bmp");

   bitmap_image red_channel_image;
   image.export_color_plane(bitmap_image::red_plane,red_channel_image);
   red_channel_image.save_image("red_channel_image.bmp");

   bitmap_image green_channel_image;
   image.export_color_plane(bitmap_image::green_plane,green_channel_image);
   green_channel_image.save_image("green_channel_image.bmp");

   bitmap_image blue_channel_image;
   image.export_color_plane(bitmap_image::blue_plane,blue_channel_image);
   blue_channel_image.save_image("blue_channel_image.bmp");
}

inline void test07()
{
   std::string file_name = "image.bmp";
   bitmap_image image("image.bmp");
   image.convert_to_grayscale();
   image.save_image("grayscale_image.bmp");
}

inline void test08()
{
   std::string file_name = "image.bmp";
   bitmap_image image("image.bmp");

   bitmap_image image1;
   bitmap_image image2;
   bitmap_image image3;
   bitmap_image image4;

   unsigned int w = image.width();
   unsigned int h = image.height();

   if(!image.region(0,0, w / 2, h / 2,image1))
   {
      std::cout << "ERROR: upper_left_image" << std::endl;
   }

   if(!image.region((w - 1) / 2, 0, w / 2, h / 2,image2))
   {
      std::cout << "ERROR: upper_right_image" << std::endl;
   }

   if(!image.region(0,(h - 1) / 2, w / 2, h / 2,image3))
   {
      std::cout << "ERROR: lower_left_image" << std::endl;
   }

   if(!image.region((w - 1) / 2, (h - 1) / 2, w / 2, h / 2,image4))
   {
      std::cout << "ERROR: lower_right_image" << std::endl;
   }

   image1.save_image("upper_left_image.bmp");
   image2.save_image("upper_right_image.bmp");
   image3.save_image("lower_left_image.bmp");
   image4.save_image("lower_right_image.bmp");
}

inline void test09()
{
   const unsigned int dim = 1000;
   bitmap_image image(dim,dim);
   for(unsigned int x = 0; x < dim; ++x)
   {
      for(unsigned int y = 0; y < dim; ++y)
      {
         rgb_store col = jet_colormap[(x + y) % dim];
         image.set_pixel(x,y,col.red,col.green,col.blue);
      }
   }
   image.save_image("color_map_image.bmp");
}

inline void test10()
{
   std::string file_name = "image.bmp";
   bitmap_image image("image.bmp");
   image.invert_color_planes();
   image.save_image("inverted_color_image.bmp");
}

inline void test11()
{
   std::string file_name = "image.bmp";
   bitmap_image image("image.bmp");

   for(unsigned int i = 0; i < 10; ++i)
   {
      image.add_to_color_plane(bitmap_image::red_plane,10);
      image.save_image(static_cast<char>(48 + i) + std::string("_red_inc_image.bmp"));
   }
}

inline void test12()
{
   std::string file_name = "image.bmp";
   bitmap_image image("image.bmp");

   double* y  = new double [image.pixel_count()];
   double* cb = new double [image.pixel_count()];
   double* cr = new double [image.pixel_count()];

   image.export_ycbcr(y,cb,cr);

   for(unsigned int i = 0; i < image.pixel_count(); ++i)
   {
      cb[i] = cr[i] = 0.0;
   }
   image.import_ycbcr(y,cb,cr);
   image.save_image("only_y_image.bmp");
}

inline void test13()
{
   std::string file_name = "image.bmp";
   bitmap_image image("image.bmp");

   double* y  = new double [image.pixel_count()];
   double* cb = new double [image.pixel_count()];
   double* cr = new double [image.pixel_count()];

   image.export_ycbcr(y,cb,cr);

   for(unsigned int j = 0; j < 10; ++j)
   {
      for(unsigned int i = 0; i < image.pixel_count(); ++i)
      {
         y[i] += 15.0;
      }
      image.import_ycbcr(y,cb,cr);
      image.save_image(static_cast<char>(48 + j) + std::string("_y_image.bmp"));
   }
}

inline void test14()
{
   bitmap_image image(1024,1024);
   image.clear();

   double c1 = 0.9;
   double c2 = 0.5;
   double c3 = 0.3;
   double c4 = 0.7;

   ::srand(0xA5AA5AA5);
   plasma(image,0,0,image.width(),image.height(),c1,c2,c3,c4,3.0,jet_colormap);
   image.save_image("plasma.bmp");
}

inline void test15()
{
   bitmap_image image("image.bmp");

   double c1 = 0.9;
   double c2 = 0.5;
   double c3 = 0.3;
   double c4 = 0.7;

   bitmap_image plasma_image(image.width(),image.height());
   plasma(plasma_image,0,0,plasma_image.width(),plasma_image.height(),c1,c2,c3,c4,3.0,jet_colormap);

   bitmap_image temp_image(image);

   temp_image.alpha_blend(0.1, plasma_image);
   temp_image.save_image("alpha_0.1.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.2, plasma_image);
   temp_image.save_image("alpha_0.2.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.3, plasma_image);
   temp_image.save_image("alpha_0.3.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.4, plasma_image);
   temp_image.save_image("alpha_0.4.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.5, plasma_image);
   temp_image.save_image("alpha_0.5.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.6, plasma_image);
   temp_image.save_image("alpha_0.6.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.7, plasma_image);
   temp_image.save_image("alpha_0.7.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.8, plasma_image);
   temp_image.save_image("alpha_0.8.bmp");
   temp_image = image;

   temp_image.alpha_blend(0.9, plasma_image);
   temp_image.save_image("alpha_0.9.bmp");
}

inline void test16()
{
   bitmap_image image(1024,1024);

   double c1 = 0.9;
   double c2 = 0.5;
   double c3 = 0.3;
   double c4 = 0.7;

   plasma(image,0,0,image.width(),image.height(),c1,c2,c3,c4,3.0,jet_colormap);

   image_drawer draw(image);

   draw.pen_width(3);
   draw.pen_color(255,0,0);
   draw.circle(image.width() / 2 + 100, image.height() / 2, 100);

   draw.pen_width(2);
   draw.pen_color(0,255,255);
   draw.ellipse(image.width() / 2, image.height() / 2, 200,350);

   draw.pen_width(1);
   draw.pen_color(255,255,0);
   draw.rectangle(50,50,250,400);

   draw.pen_color(0,255,0);
   draw.rectangle(450,250,850,880);

   image.save_image("image_drawer.bmp");
}

inline void test17()
{
   bitmap_image image(1000,180);
   image_drawer draw(image);
   const rgb_store* colormap[9] = {
                                   autumn_colormap,
                                   copper_colormap,
                                   gray_colormap,
                                   hot_colormap,
                                   hsv_colormap,
                                   jet_colormap,
                                   prism_colormap,
                                   vga_colormap,
                                   yarg_colormap
                                  };

   for(unsigned int i = 0; i < image.width(); ++i)
   {
      for(unsigned int j = 0; j < 9; ++j)
      {
         draw.pen_color(colormap[j][i].red,colormap[j][i].green,colormap[j][i].blue);
         draw.vertical_line_segment(j * 20, (j + 1) * 20, i);
      }
   }
   image.save_image("color_maps.bmp");
}

int main(void)
{
   test01();
   test02();
   test03();
   test04();
   test05();
   test06();
   test07();
   test08();
   test09();
   test10();
   test11();
   test12();
   test13();
   test14();
   test15();
   test16();
   test17();
   return 0;
}
