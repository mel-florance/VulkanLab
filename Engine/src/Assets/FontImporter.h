#ifndef VULKANLAB_FONT_IMPORTER_H
#define VULKANLAB_FONT_IMPORTER_H

class FontImporter {
public:
    FontImporter();
    ~FontImporter();

    void import(const char* filename);
    static void parsingCallback(void *args, void *_font_data, int error);

private:
};

#endif //VULKANLAB_FONT_IMPORTER_H
