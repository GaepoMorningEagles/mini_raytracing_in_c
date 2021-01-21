#ifndef STRUCTURES_H
# define STRUCTURES_H

// 1. 공용 구조체
typedef struct s_vec3	t_vec3;
typedef struct s_vec3	t_point3;
typedef struct s_vec3	t_color3;
typedef struct s_ray	t_ray;
typedef struct s_hit_record t_hit_record;

// 2. 장면 구조체
typedef struct s_camera	t_camera;
typedef struct s_canvas	t_canvas;
typedef struct s_scene	t_scene;

// 3. 오브젝트 구조체
typedef struct s_object t_object;
typedef struct s_sphere	t_sphere;
typedef struct s_light	t_light;

// 4. 식별자 매크로
typedef int				t_bool;
# define FALSE 0
# define TRUE 1

typedef int				t_object_type;
# define SP 0
# define LIGHT_POINT 1

// 엄청 작은 값
# define EPSILON 1e-6

// 공용 구조체
struct s_vec3
{
	double x;
	double y;
	double z;
};

struct	s_ray
{
	t_point3	orig;
	t_vec3		dir;
};

struct s_hit_record
{
	t_point3	p;
	t_vec3		normal;
	double		tmin;
	double		tmax;
	double		t;
	t_bool		front_face;
};

// 장면 구조체
struct	s_camera
{
	t_point3	orig;  // 카메라 원점(위치)
	double		viewport_h; // 뷰포트 세로길이
	double		viewport_w; // 뷰포트 가로길이
	t_vec3		horizontal; // 수평길이 벡터
	t_vec3		vertical; // 수직길이 벡터
	double		focal_len; // focal length
	t_point3	left_bottom; // 왼쪽 아래 코너점
};

struct	s_canvas
{
	int		width; //canvas width
	int		height; //canvas height;
	double	aspect_ratio; //종횡비
};

struct						s_scene
{
	t_canvas		canvas;
	t_camera		camera;
	t_object		*world;
	t_object		*light;
	t_ray			ray;
	t_hit_record	rec;
};

// 오브젝트 구조체
struct						s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
};

struct	s_sphere
{
	t_point3	center;
	double		radius;
	double		radius2;
};

struct						s_light
{
	t_point3		origin;
	t_color3		light_color;
	double			bright_ratio;
};

#endif
