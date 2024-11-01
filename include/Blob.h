#ifndef BLOB_H
#define BLOB_H
#include "definitions.h"
#include "Gem.h"

class Blob
{
    public:
        // special members
        Blob();
        virtual ~Blob();

        // getters
        auto get_blob() -> blob_t*;
        auto get_floor() const -> floor_t;

        // stats
        auto count_connectors() const -> count_t;
        auto count_gems_in_blob() const -> count_t;
        auto measure_blob_height() const -> span_t;
        auto count_gems_to_destroy() const -> count_t;
        auto measure_longest_connector() const -> span_t;
        auto count_gems_of_color(color_t) const -> count_t;
        auto count_connectors_to_destroy() const -> count_t;
        auto count_gems_to_destroy_of_color(color_t) const -> count_t;

        // checkers
        auto gems_are_adjacent(const gem_raw_ptr const, const gem_raw_ptr const) const -> bool;

        // actions
        auto clear_blob() -> void;
        auto update_floor() -> void;
        auto destroy_connectors() -> blob_t;
        auto add_gem_to_blob(gem_uptr) -> void;

    private:
        blob_t blob;
        floor_t floor;
};

#endif // BLOB_H
