#include "ImGuiMatrixRenderer.h"

#include <imgui.h>

namespace ImGui
{
	void RenderMatrix(const AI::Matrix& matrix, const size_t cellSize = 10)
	{
		ImVec2 contentPos = ImGui::GetWindowContentRegionMin();
		contentPos.x += ImGui::GetWindowPos().x;
		contentPos.y += ImGui::GetWindowPos().y;

		const size_t length{ 28 };
		for (size_t i = 0; i < length; ++i)
		{
			for (size_t j = 0; j < length; ++j)
			{
				const size_t color = matrix(j * length + i, 0) * 255;
				ImGui::GetWindowDrawList()->AddRectFilled(
					ImVec2(contentPos.x + cellSize * i, contentPos.y + cellSize * j),
					ImVec2(contentPos.x + cellSize * (i + 1), contentPos.y + cellSize * (j + 1)),
					IM_COL32(color, color, color, 255)
				);
			}
		}
	}
}