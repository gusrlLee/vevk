#pragma warning(disable : 4819)
#include <iostream>
#include "vevk/vevk.h"

class Application : public vevk::IBaseApplication{
public:

private:

};

int main() {
    
    // vevk init (glfw and logging system)
    vevk::init();
    auto app = std::make_shared<Application>();
    app->prepare();

    app->run();

    app->destroy();
    vevk::terminate();
    return 0;
}