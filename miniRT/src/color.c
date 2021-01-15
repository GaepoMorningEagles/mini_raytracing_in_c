#include "color.h"

// [0,1] 로 되어있는 rgb 값을 각각 [0,255]에 맵핑 해서 출력.
void	write_color(t_color3 pixel_color)
{
	printf("%d %d %d\n", (int)(255.999 * pixel_color.x),
						(int)(255.999 * pixel_color.y),
						(int)(255.999 * pixel_color.z));
}
