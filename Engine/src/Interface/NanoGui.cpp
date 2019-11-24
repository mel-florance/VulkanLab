#include "NanoGui.h"
#include <glm/glm.hpp>
#include <nanogui/nanogui.h>
#include "../Core/Engine.h"
#include "../Display/Window.h"
using namespace nanogui;

NanoGui::NanoGui(Engine* engine) {
    nanogui::init();
    Screen *screen = new Screen();
    screen->initialize(engine->getWindow()->getInstance(), false);

    bool enabled = true;
    FormHelper *gui = new FormHelper(screen);
    ref<nanogui::Window> win = gui->add_window(Vector2i(10, 10), "Form helper example");
    gui->add_group("Basic types");
    bool bvar = true;
    gui->add_variable("bool", bvar);

    screen->set_visible(true);
    screen->perform_layout();
    win->center();

    nanogui::mainloop();
}

NanoGui::~NanoGui() {

}
