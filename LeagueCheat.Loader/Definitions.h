#pragma once

#define SAFE_DELETE_PTR(x) if (x) { delete x; x = nullptr; }