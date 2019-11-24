#include <thread>
#include <cstring>
#include "FontImporter.h"
#define TTF_FONT_PARSER_IMPLEMENTATION
#include <ttf-parser/ttfParser.h>

FontImporter::FontImporter() {
}

FontImporter::~FontImporter() {
}

void FontImporter::import(const char* filename) {
    uint8_t condition_variable = 0;

    TTFFontParser::FontData font_data;
    int8_t error = TTFFontParser::parse_file(filename, &font_data, &FontImporter::parsingCallback, &condition_variable);

    while (!condition_variable) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void FontImporter::parsingCallback(void *args, void *_font_data, int error) {
    if (error) {
        *(uint8_t *) args = error;
        printf("Unable to parse font\n");
    } else {
        TTFFontParser::FontData *font_data = (TTFFontParser::FontData *) _font_data;
        printf("Font %s parsed\n", font_data->full_font_name.c_str());
        printf("Number of glyphs: %d\n", font_data->glyphs.size());
        *(uint8_t *) args = 1;
    }
}
