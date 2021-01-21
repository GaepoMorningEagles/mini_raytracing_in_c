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

/*
	(ambient + diffuse + specular) * objectColor * 감쇠율;
	vec3 lightDir = normalize(lightPos - FragPos);

	ambient
		float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;

	diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	Specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;
	vec3 result = (ambient + diffuse + specular) * objectColor;
*/

t_vec3			reflect(t_vec3 v, t_vec3 n)
{
	//v - 2 * dot(v, n) * n;
	return (vminus(v, vmult(n ,vdot(v, n) * 2)));
}

t_color3		point_light_get(t_scene *scene, t_light *light)
{
	t_color3	ambient;
	t_color3	diffuse;
	t_color3	specular;
	t_vec3		light_dir;
	t_vec3		view_dir;
	t_vec3		reflect_dir;

	double		ka;
	double		kd;
	double		ks;
	double		ksn;
	double		spec;
	double		brightness;

	view_dir = vunit(vmult(scene->ray.dir, -1));
	light_dir = vunit(vminus(light->origin, scene->rec.p));
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
