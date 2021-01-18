#include "trace.h"

void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	// 광선의 방향벡터와 교점의 법선벡터의 내적이 음수이면 광선은 앞면(객체의)에 hit 한 것이다
	rec->front_face = vdot(r->dir, rec->normal) < 0;
	// 광선의 앞면에 hit 면 그대로 아니면 법선을 반대로 뒤집는다. (항상 광선 방향벡터와 법선 벡터를 반대인 상태로 사용하기위해)
	rec->normal = (rec->front_face) ? rec->normal : vmult(rec->normal, -1);
}
