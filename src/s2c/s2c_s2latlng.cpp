
struct s2c_S2LatLng {
	void *obj;
};

s2c_S2LatLng_t *s2c_S2LatLng_new(double lat, double lon) {
	s2c_S2LatLng_t *m;
    S2LatLng *obj;
    
	m = (typeof(m))malloc(sizeof(*m));
	*obj = S2LatLng::FromDegrees(lat, lon);
	m->obj = obj;

	return m;
}

#define CAST_LATLNG(p) (static_cast<S2LatLng *>((p)->obj))

void s2c_S2LatLng_free(s2c_S2LatLng_t *m) {
    if (m == NULL)
		return;
	delete CAST_LATLNG(m);
	free(m);    
}

void s2c_S2LatLng_latlng(s2c_S2LatLng_t *m, double *lat, double *lng) {
    *lat = CAST_LATLNG(m)->lat().degrees();
    *lng = CAST_LATLNG(m)->lng().degrees();
}

bool s2c_S2LatLng_eq(s2c_S2LatLng_t *A, s2c_S2LatLng_t *B) {
    return CAST_LATLNG(A) == CAST_LATLNG(B);
}
