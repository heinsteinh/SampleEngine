

#include <glm/gtc/matrix_transform.hpp>
#include <toml.hpp>


#define VE_FONTCACHE_FREETYPE_RASTERISATION
#ifdef VE_FONTCACHE_FREETYPE_RASTERISATION
	#include <ft2build.h>
	#include FT_FREETYPE_H
    #include FT_GLYPH_H
#endif // VE_FONTCACHE_FREETYPE_RASTERISATION

#define DEMO_HARFBUZZ
#ifdef DEMO_HARFBUZZ
	#define VE_FONTCACHE_HARFBUZZ
    #include <hb.h>
#endif // DEMO_HARFBUZZ

class Person
{
private:
    /* data */
public:
    Person(/* args */);
    ~Person();
};