void s2c_point_to_cell(pgs2_S2Point* point, pgs2_S2Cell* cell, error_cb) {
    try {
        S2Point P = S2Point(point->x, point->y, point->z);
        cell->id = S2CellId(P).id();
    } CATCH_ALL(error_cb)
}

void s2c_point_to_latlng(pgs2_S2Point* point, pgs2_S2LatLng* ll, error_cb) {
    try {
        S2Point P = S2Point(point->x, point->y, point->z);
        S2LatLng L = S2LatLng(P);
        ll->lat = L.lat().radians();
        ll->lng = L.lng().radians();
    } CATCH_ALL(error_cb)
}
