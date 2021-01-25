#ifndef TRACE_H
# define TRACE_H

# include "structures.h"
# include "utils.h"

// trace/ray/
t_ray		ray(t_point3 orig, t_vec3 dir);
t_ray		ray_primary(t_camera *cam, double u, double v);
t_point3	ray_at(t_ray *ray, double t);
t_color3	ray_color(t_scene *scene);
t_color3	phong_lighting(t_scene *scene);
t_color3	point_light_get(t_scene *scene, t_light *light);

// trace/hit/
t_bool		hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
double		hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec);
void		set_face_normal(t_ray *r, t_hit_record *rec);

#endif
