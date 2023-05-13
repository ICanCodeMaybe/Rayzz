#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>

#include "hittable.h"

class HittableList : public Hittable{
public:
	std::vector<std::shared_ptr<Hittable>> hittable_list;
public:

	HittableList(){}
	HittableList(std::shared_ptr<Hittable> object){ add(object); }

	void add(std::shared_ptr<Hittable> object) { hittable_list.push_back(object); }
	void clear(){ hittable_list.clear(); };

	virtual bool hit(const Ray& r, double t_min, double t_max, hit_info& hit_in) const override;
};

bool HittableList::hit(const Ray& r, double t_min, double t_max, hit_info& hit_in) const{
	hit_info temporary_info;
	bool hit_any = false;
	double closest_so_far = t_max;

	for(const auto obj : hittable_list){
		if(obj->hit(r, t_min, closest_so_far, temporary_info)){
			hit_any = true;
			hit_in = temporary_info;
			closest_so_far = hit_in.t;
		}
	}

	return hit_any;
}


#endif
