
void s2c_xyz_from_id(uint64_t id, double *x, double *y, double *z) {
    S2CellId cell = S2CellId(id);
    S2Point point = cell.ToPoint();
    *x = point.x();
    *y = point.y();
    *z = point.z();
}

void s2c_xyz_to_id(double x, double y, double z, uint64_t *id) {
    S2Point point = S2Point(x, y, z);
    *id = S2CellId(point.Normalize()).id();
}

void s2c_xyz_to_latlng(double x, double y, double z, double *lat, double *lng) {
    S2Point point = S2Point(x, y, z);
    S2LatLng ll = S2LatLng(point);
    *lat = ll.lat().radians();
    *lng = ll.lng().radians();
}
