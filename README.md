# ProgressDisplay

A small single-header C++ progress display for terminal output.

## Features

- header-only
- writes progress updates to any `std::ostream`
- supports optional prefix and suffix text
- clamps `update()` values to `total`
- uses overflow-safe `increment()`
- flushes output on each display update
- handles `total == 0`

## File

- `progress_display.hpp`

## Usage

```cpp
#include "progress_display.hpp"
#include <iostream>

int main() {
    ProgressDisplay progress(10, std::cout, "Downloading", "items");

    for (int i = 0; i < 10; ++i) {
        progress.increment();
    }

    progress.finish();
}
```

Example output:

```text
Downloading 100% 10/10 items
```

## API

### `ProgressDisplay(uintmax_t total, std::ostream& output_stream, const std::string& prefix = "", const std::string& suffix = "")`
Creates a progress display.

- `total`: total number of steps
- `output_stream`: destination stream, such as `std::cout`
- `prefix`: optional text printed before the percentage
- `suffix`: optional text printed after the `current/total` counter

### `void update(uintmax_t new_current)`
Sets the current progress value and clamps it to `total`.

### `void increment(uintmax_t amount = 1)`
Advances progress by `amount` without overflowing. If the increment would pass `total`, it stops at `total`.

### `std::string progress_string() const`
Builds the current progress line.

### `void display()`
Writes the current progress line to the output stream and flushes it.

### `void finish()`
Sets progress to `total`, displays the final line, and prints a newline.

## Notes

- The displayed line begins with `\r`, so repeated updates overwrite the same terminal line.
- If `total == 0`, the displayed percentage is `100%`.
- `finish()` is recommended so the final output ends with a newline.
