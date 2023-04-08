#pragma once

#define ENGINE_MIN(x, y) (((x) < (y)) ? (x) : (y))
#define ENGINE_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define ENGINE_PIN(a, min_value, max_value) ENGINE_MIN(max_value, ENGINE_MAX(a, min_value))

#define ENGINE_VALID_INDEX(idx, range) (((idx) >= 0) && ((idx) < (range)))
#define ENGINE_PIN_INDEX(idx, range) ENGINE_PIN(idx, 0, (range)-1)

#define ENGINE_SIGN(x) ((((x) > 0.0f) ? 1.0f : 0.0f) + (((x) < 0.0f) ? -1.0f : 0.0f))
