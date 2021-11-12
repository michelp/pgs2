void s2c_xyz_from_id(uint64_t id, double *x, double *y, double *z, error_cb cb) {
    try {
        S2CellId cell = S2CellId(id);
        S2Point point = cell.ToPoint();
        *x = point.x();
        *y = point.y();
        *z = point.z();
    } CATCH_ALL(error_cb)
}

void s2c_xyz_to_id(double x, double y, double z, uint64_t *id, error_cb cb) {
    try {
        S2Point point = S2Point(x, y, z);
        *id = S2CellId(point.Normalize()).id();
    } CATCH_ALL(error_cb)
}

void s2c_xyz_to_latlng(double x, double y, double z, double *lat, double *lng, error_cb) {
    try {
        S2Point point = S2Point(x, y, z);
        S2LatLng ll = S2LatLng(point);
        *lat = ll.lat().radians();
        *lng = ll.lng().radians();
    } CATCH_ALL(error_cb)
}
