
void s2c_xyz_from_id(uint64_t id, double *x, double *y, double *z, error_cb cb);
void s2c_xyz_to_id(double x, double y, double z, uint64_t *id, error_cb cb);
void s2c_xyz_to_latlng(double x, double y, double z, double *lat, double *lng, error_cb cb);
