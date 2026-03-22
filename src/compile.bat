g++ main.cpp glad.c World/world.cpp ^
	Game/game.cpp Clock/clock.cpp ^
	Graphics/graphics.cpp Entities/entities.cpp ^
	Player/player.cpp Blocktypes/blocktypes.cpp ^
	../imgui/imgui.cpp ^
	../imgui/imgui_draw.cpp ^
	../imgui/imgui_tables.cpp ^
	../imgui/imgui_widgets.cpp ^
	../imgui/backends/imgui_impl_glfw.cpp ^
	../imgui/backends/imgui_impl_opengl3.cpp ^
	-I../include -I../imgui -I../imgui/backends -L../lib ^
	-lglfw3dll -lopengl32 -lgdi32 ^
	-o ../build/main.exe
