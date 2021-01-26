#include "trace.h"

t_color3		phong_lighting(t_scene *scene)
{
	t_color3	light_color;
	t_object	*lights;

	light_color = color3(0, 0, 0);
	lights = scene->light;
	while(lights)
	{
		if(lights->type == LIGHT_POINT)
			light_color = vplus(light_color, point_light_get(scene, lights->element));
		lights = lights->next;
	}
	// dprintf(2,"light_color:%f, %f, %f\n", light_color.x, light_color.y, light_color.z);
	return (vmin(vmult_(light_color, scene->rec.albedo), color3(1, 1, 1)));
}

t_vec3			reflect(t_vec3 v, t_vec3 n)
{
	//v - 2 * dot(v, n) * n;
	return (vminus(v, vmult(n ,vdot(v, n) * 2)));
}

t_bool			in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hit_record rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}

t_color3		point_light_get(t_scene *scene, t_light *light)
{
	t_color3	ambient;
	t_color3	diffuse;
	t_color3	specular;
	t_vec3		light_dir;
	double		light_len;
	t_ray		light_ray;
	t_vec3		view_dir;
	t_vec3		reflect_dir;

	double		ka;
	double		kd;
	double		ks;
	double		ksn;
	double		spec;
	double		brightness;

	light_dir = vminus(light->origin, scene->rec.p);
	light_len = vlength(light_dir);
	light_ray = ray(vplus(scene->rec.p, vmult(scene->rec.normal, EPSILON)), light_dir);
	if (in_shadow(scene->world, light_ray, light_len))
		return (color3(0,0,0));
	light_dir = vunit(light_dir);
	view_dir = vunit(vmult(scene->ray.dir, -1));
	reflect_dir = reflect(vmult(light_dir, -1), scene->rec.normal);
	ka = 0.1; // ambient strength;
	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);// diffuse strength;
	ks = 0.5; // specular strength;
	ksn = 64;
	ambient = vmult(light->light_color, ka);
	diffuse = vmult(light->light_color, kd);
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vmult(vmult(light->light_color, kd), spec);
	brightness = light->bright_ratio * LUMEN; // 기준 광속/광량을 정의한 매크로
	return (vmult(vplus(vplus(ambient, diffuse), specular), brightness));
}
