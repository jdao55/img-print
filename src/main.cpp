#include <Magick++.h>
#include "fmt/format.h"

using namespace std;
using namespace Magick;

int main(int argc,char **argv)
{
  InitializeMagick(*argv);

  // Construct the image object. Seperating image construction from the
  // the read operation ensures that a failure to read the image file
  // doesn't render the image object useless.
  Image image;
  try {
    // Read a file into image object
    image.read(argv[1] );

    // Crop the image to specified size (width, height, xOffset, yOffset)
    image.crop( Geometry(100,100, 100, 100) );

    // Write the image to a file
    image.write( "logo.png" );
  }
  catch( Exception &error_ )
    {
        fmt::print("error");
      return 1;
    }
  return 0;
}
