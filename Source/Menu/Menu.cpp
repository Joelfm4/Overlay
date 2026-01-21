#include "Menu.h"


void Menu::Display() noexcept {

    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_Once);

    ImGui::Begin("Last", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);


    // ################## Sidebar

    static int tab = 0;

    ImGui::BeginChild("Sidebar", ImVec2(150, 0), true);
    {
        ImGui::Separator();

        if (ImGui::Selectable("General", tab == 0)) tab = 0;
        if (ImGui::Selectable("Settings", tab == 1)) tab = 1;

    }
    ImGui::EndChild();

    // ################## 


    // ################## Display

    ImGui::SameLine();

    ImGui::BeginChild("Content", ImVec2(0, 0), true);
    {

        switch (tab) {

			case 0:
            {

                ImGui::BeginChild("Option1", ImVec2((ImGui::GetContentRegionAvail().x - 10) * 0.5f, 250), true);
                {

                    ImGui::TextColored(ImVec4(0.6f, 0.8f, 0.4f, 1.0f), "Option 1");

                    ImGui::Separator();

                    ImGui::Text("A lot of text");

                }
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::BeginChild("Option2", ImVec2(0, 250), true);
                {

                    ImGui::TextColored(ImVec4(0.6f, 0.8f, 0.4f, 1.0f), "Option 2");

                    ImGui::Separator();

                    ImGui::Text("A lot of text");

                }
                ImGui::EndChild();

                // Second Row
                ImGui::BeginChild("Option3", ImVec2((ImGui::GetContentRegionAvail().x - 10) * 0.5f, 0), true);
                {

                    ImGui::TextColored(ImVec4(0.6f, 0.8f, 0.4f, 1.0f), "Option 3");

                    ImGui::Separator();

                    ImGui::Text("A lot of text");

                }
                ImGui::EndChild();

                ImGui::SameLine();

                ImGui::BeginChild("Option4", ImVec2(0, 0), true);
                {

                    ImGui::TextColored(ImVec4(0.6f, 0.8f, 0.4f, 1.0f), "Option 4");

                    ImGui::Separator();

                    ImGui::Text("A lot of text");

                }
                ImGui::EndChild();

				break;

            }

			case 1:
				ImGui::Text("Settings");
				break;

			default:
				ImGui::Text("Unknown tab");
				break;
			}

    }
    ImGui::EndChild();

    // ################## 


    ImGui::End();
}

