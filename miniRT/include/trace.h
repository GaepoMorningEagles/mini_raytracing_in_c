#ifndef TRACE_H
# define TRACE_H

# include "structures.h"
# include "utils.h"

// trace/ray/
t_ray		ray(t_point3 orig, t_vec3 dir);
t_ray		ray_primary(t_camera *cam, double u, double v);
t_point3	ray_at(t_ray *ray, double t);
t_color3	ray_color(t_ray *ray, t_sphere *sphere);

// trace/hit/
t_bool		hit_sphere(t_sphere *sp, t_ray *ray);

#endif

