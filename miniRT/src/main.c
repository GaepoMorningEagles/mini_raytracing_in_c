#include <stdio.h>
#include "structures.h"
#include "utils.h"
#include "color.h"

int	main(void)
{
	int			i;
	int			j;
	t_color3	pixel_color;
	int			canvas_width;
	int			canvas_height;

	//캔버스의 가로, 세로 픽셀값
	canvas_width = 256;
	canvas_height = 256;

	// 랜더링
	// P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
	printf("P3\n%d %d\n255\n", canvas_width, canvas_height);
	j = canvas_height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < canvas_width)
		{
		pixel_color.x = (double)i / (canvas_width - 1);
			pixel_color.y = (double)j / (canvas_height - 1);
			pixel_color.z = 0.25;
			write_color(pixel_color);
		++i;
		}
	--j;
	}
	return (0);
}
