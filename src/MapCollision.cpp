#include <algorithm>
#include <array>
#include <chrono>
#include <vector>
#include <cmath>

#include "Headers/Global.hpp"
#include "Headers/MapCollision.hpp"

unsigned char map_collision(float i_x, float i_y, const std::vector<Cell>& i_check_cells, const Map& i_map)
{
    float cell_x = i_x / CELL_SIZE;
    float cell_y = i_y / CELL_SIZE;
    unsigned char output = 0;

    for (unsigned char a = 0; a < 4; a++)
    {
        short x, y;

        switch (a)
        {
            case 0:
                x = floor(cell_x);
                y = floor(cell_y);
                break;
            case 1:
                x = ceil(cell_x);
                y = floor(cell_y);
                break;
            case 2:
                x = floor(cell_x);
                y = ceil(cell_y);
                break;
            case 3:
                x = ceil(cell_x);
                y = ceil(cell_y);
        }

        if (x >= 0 && x < i_map.size() && y >= 0 && y < i_map[0].size())
        {
            if (std::find(i_check_cells.begin(), i_check_cells.end(), i_map[x][y]) != i_check_cells.end())
            {
                output += 1 << a; // Binary 0001, 0010, 0100, or 1000.
            }
        }
        else if (std::find(i_check_cells.begin(), i_check_cells.end(), Cell::Wall) != i_check_cells.end())
        {
            output += 1 << a;
        }
    }

    return output;
}
