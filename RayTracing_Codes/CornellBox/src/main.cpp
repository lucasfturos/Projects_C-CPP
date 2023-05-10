#include "./Render/render.hpp"

int main() {
    auto render{make_shared<Render>()};
    render->run();
}
