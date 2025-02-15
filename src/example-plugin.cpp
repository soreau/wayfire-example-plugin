/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Scott Moreau <oreaus@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <wayfire/view.hpp>
#include <wayfire/plugin.hpp>
#include <wayfire/per-output-plugin.hpp>
#include <wayfire/plugins/common/input-grab.hpp>

class wayfire_example_plugin : public wf::per_output_plugin_instance_t, public wf::pointer_interaction_t
{
    std::unique_ptr<wf::input_grab_t> input_grab;

  public:
    void init() override
    {
        LOGI("Hello World!");

        wf::plugin_activation_data_t grab_interface = {
            .name = "example-plugin",
            .capabilities = wf::CAPABILITY_GRAB_INPUT,
        };
        input_grab = std::make_unique<wf::input_grab_t>("example-plugin", output, nullptr, this, nullptr);
        input_grab->grab_input(wf::scene::layer::OVERLAY);
    }

    void handle_pointer_motion(wf::pointf_t pointer_position, uint32_t time_ms) override
    {
        LOGI("Pointer: ", pointer_position.x, ",", pointer_position.y);
    }

    void fini() override
    {
        LOGI("Goodbye, Cruel World..");
        input_grab->ungrab_input();
    }
};

DECLARE_WAYFIRE_PLUGIN(wf::per_output_plugin_t<wayfire_example_plugin>);
