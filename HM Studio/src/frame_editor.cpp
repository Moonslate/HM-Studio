#include "frame_editor.hpp"

static uint8_t* prevScriptRgb = new uint8_t[768]{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x89, 0xbc, 0x3b, 0x97, 0xc4, 0x49, 0x9d, 0xc7, 0x38, 0x95, 0xc3, 0x04, 0x79, 0xb3, 0x07, 0x7a, 0xb4, 0x07, 0x7a, 0xb4, 0x08, 0x7a, 0xb4, 0x0a, 0x7c, 0xb5, 0x0f, 0x7f, 0xb6, 0x14, 0x81, 0xb8, 0xe0, 0xee, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x85, 0xbe, 0xda, 0xa7, 0xcf, 0xe4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xba, 0xda, 0xe9, 0xc9, 0xe2, 0xee, 0x4f, 0x9f, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x88, 0xba, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfe, 0xfe, 0xfb, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x41, 0x99, 0xc6, 0xc2, 0xdf, 0xec, 0x34, 0x92, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x9e, 0xc8, 0xff, 0xff, 0xff, 0xf3, 0xf9, 0xfc, 0xf1, 0xf8, 0xfb, 0xf1, 0xf8, 0xfb, 0xf1, 0xf8, 0xfb, 0xf1, 0xf8, 0xfb, 0xf2, 0xf8, 0xfb, 0xf5, 0xfa, 0xfc, 0xff, 0xff, 0xff, 0x01, 0x77, 0xb2, 0x1c, 0x85, 0xba, 0x22, 0x89, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf4, 0xf9, 0xfc, 0x56, 0xa5, 0xcc, 0xff, 0xff, 0xff, 0xeb, 0xf6, 0xf9, 0xea, 0xf5, 0xf9, 0xeb, 0xf5, 0xf9, 0xeb, 0xf5, 0xf9, 0xeb, 0xf5, 0xf9, 0xeb, 0xf5, 0xf9, 0xf5, 0xfa, 0xfc, 0xfd, 0xfe, 0xfe, 0x36, 0x8e, 0xb9, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xce, 0xe4, 0xef, 0x88, 0xbf, 0xdb, 0xff, 0xff, 0xff, 0xe5, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xf6, 0xfa, 0xfd, 0xc8, 0xe2, 0xee, 0x55, 0x9d, 0xc2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0xc3, 0xda, 0x59, 0x99, 0x46, 0x76, 0xa0, 0x00, 0x30, 0x7b, 0x00, 0xdd, 0xee, 0xf5, 0xdd, 0xee, 0xf5, 0xdd, 0xee, 0xf5, 0xdd, 0xee, 0xf5, 0xdc, 0xee, 0xf5, 0xfa, 0xfc, 0xfe, 0xa3, 0xcf, 0xe4, 0x77, 0xaf, 0xca, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x74, 0xa5, 0x46, 0x7e, 0xa9, 0x00, 0xd4, 0xe1, 0x71, 0x38, 0x80, 0x00, 0xd6, 0xea, 0xf2, 0xd6, 0xea, 0xf2, 0xd6, 0xea, 0xf3, 0xd6, 0xea, 0xf3, 0xd5, 0xea, 0xf3, 0xff, 0xff, 0xff, 0x79, 0xb8, 0xd6, 0x9b, 0xc1, 0xd5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0xb3, 0x59, 0x7f, 0xae, 0x00, 0xc4, 0xda, 0x58, 0xd5, 0xe4, 0x80, 0x37, 0x7f, 0x00, 0x37, 0x7f, 0x00, 0x36, 0x7e, 0x00, 0x34, 0x7d, 0x00, 0x74, 0xa8, 0x47, 0xce, 0xe7, 0xf0, 0xff, 0xff, 0xff, 0x4b, 0x9f, 0xc9, 0xc2, 0xd8, 0xe3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0xb1, 0x53, 0x81, 0xb2, 0x00, 0xc7, 0xe0, 0x60, 0x97, 0xc3, 0x00, 0xd8, 0xe8, 0x93, 0xd1, 0xe6, 0x4d, 0xd2, 0xe7, 0x4e, 0xd2, 0xe7, 0x4a, 0xdf, 0xec, 0x90, 0x39, 0x7f, 0x00, 0xca, 0xe3, 0xee, 0xff, 0xff, 0xff, 0x31, 0x90, 0xc1, 0xf5, 0xf5, 0xf5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0x8a, 0x00, 0xcd, 0xe6, 0x63, 0x9a, 0xca, 0x00, 0x98, 0xc8, 0x00, 0x97, 0xc7, 0x00, 0x99, 0xc8, 0x00, 0x99, 0xc8, 0x00, 0x99, 0xc8, 0x00, 0xcf, 0xe7, 0x6b, 0x3c, 0x81, 0x00, 0xd2, 0xe9, 0xf0, 0xfd, 0xfe, 0xff, 0x0a, 0x7c, 0xb5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x74, 0x9f, 0x42, 0x81, 0xb9, 0x00, 0x9f, 0xd3, 0x00, 0x9c, 0xd0, 0x00, 0x9c, 0xd0, 0x00, 0x9f, 0xd5, 0x00, 0xa1, 0xd7, 0x00, 0xa1, 0xd7, 0x00, 0xc0, 0xe7, 0x3a, 0x3c, 0x81, 0x00, 0xdc, 0xee, 0xf4, 0xe2, 0xf0, 0xf6, 0x25, 0x87, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdd, 0xdd, 0xdd, 0x75, 0xa0, 0x46, 0x80, 0xbc, 0x00, 0xa0, 0xd8, 0x00, 0xa2, 0xd9, 0x00, 0x43, 0x84, 0x00, 0x4a, 0x88, 0x00, 0x4b, 0x89, 0x00, 0x4a, 0x88, 0x00, 0x80, 0xae, 0x4c, 0xea, 0xf4, 0xf8, 0x61, 0xab, 0xcf, 0x71, 0xa9, 0xc4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xde, 0xde, 0xde, 0x75, 0xa0, 0x46, 0x80, 0xbe, 0x00, 0xa6, 0xe4, 0x00, 0x4b, 0x89, 0x00, 0x14, 0x84, 0xdd, 0x18, 0x85, 0xd0, 0x17, 0x84, 0xcb, 0x14, 0x82, 0xc4, 0x12, 0x80, 0xb7, 0x26, 0x88, 0xba, 0xe5, 0xe5, 0xe5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xde, 0xde, 0xde, 0x72, 0x9e, 0x42, 0x85, 0xc6, 0x00, 0x4f, 0x8b, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xd0, 0xd0, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xdd, 0xdd, 0xdd, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static uint8_t* prevScriptAlpha = new uint8_t[256]{ 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

static uint8_t* proxScriptRgb = new uint8_t[768]{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x89, 0xbc, 0x3b, 0x97, 0xc4, 0x49, 0x9d, 0xc7, 0x38, 0x95, 0xc3, 0x04, 0x79, 0xb3, 0x07, 0x7a, 0xb4, 0x07, 0x7a, 0xb4, 0x08, 0x7a, 0xb4, 0x0a, 0x7c, 0xb5, 0x0f, 0x7f, 0xb6, 0x14, 0x81, 0xb8, 0xe0, 0xee, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x85, 0xbe, 0xda, 0xa7, 0xcf, 0xe4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xba, 0xda, 0xe9, 0xc9, 0xe2, 0xee, 0x4f, 0x9f, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x88, 0xba, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfe, 0xfe, 0xfb, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x41, 0x99, 0xc6, 0xc2, 0xdf, 0xec, 0x34, 0x92, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x9e, 0xc8, 0xff, 0xff, 0xff, 0xf3, 0xf9, 0xfc, 0xf1, 0xf8, 0xfb, 0xf1, 0xf8, 0xfb, 0xf1, 0xf8, 0xfb, 0xf1, 0xf8, 0xfb, 0xf2, 0xf8, 0xfb, 0xf5, 0xfa, 0xfc, 0xff, 0xff, 0xff, 0x01, 0x77, 0xb2, 0x1c, 0x85, 0xba, 0x22, 0x89, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf4, 0xf9, 0xfc, 0x56, 0xa5, 0xcc, 0xff, 0xff, 0xff, 0xeb, 0xf6, 0xf9, 0xea, 0xf5, 0xf9, 0xeb, 0xf5, 0xf9, 0xeb, 0xf5, 0xf9, 0xeb, 0xf5, 0xf9, 0xeb, 0xf5, 0xf9, 0xf5, 0xfa, 0xfc, 0xfd, 0xfe, 0xfe, 0x36, 0x8e, 0xb9, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xce, 0xe4, 0xef, 0x88, 0xbf, 0xdb, 0xff, 0xff, 0xff, 0xe5, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xf6, 0xfa, 0xfd, 0xc8, 0xe2, 0xee, 0x55, 0x9d, 0xc2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0xc3, 0xda, 0xbb, 0xdb, 0xea, 0xee, 0xf7, 0xfa, 0xdd, 0xee, 0xf5, 0xdd, 0xee, 0xf5, 0xdd, 0xee, 0xf5, 0xdd, 0xee, 0xf5, 0xdd, 0xee, 0xf5, 0x30, 0x7b, 0x00, 0x76, 0xa0, 0x00, 0x59, 0x99, 0x46, 0x77, 0xaf, 0xca, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6b, 0xac, 0xcb, 0xcc, 0xe4, 0xf0, 0xe0, 0xef, 0xf6, 0xd6, 0xea, 0xf2, 0xd6, 0xea, 0xf2, 0xd6, 0xea, 0xf2, 0xd6, 0xea, 0xf3, 0xd6, 0xea, 0xf3, 0x38, 0x80, 0x00, 0xd4, 0xe1, 0x71, 0x7e, 0xa9, 0x00, 0x74, 0xa5, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x91, 0xbe, 0xff, 0xff, 0xff, 0xd2, 0xe9, 0xf1, 0xd1, 0xe8, 0xf0, 0x74, 0xa8, 0x47, 0x34, 0x7d, 0x00, 0x36, 0x7e, 0x00, 0x37, 0x7f, 0x00, 0x37, 0x7f, 0x00, 0xd5, 0xe4, 0x80, 0xc4, 0xda, 0x58, 0x7f, 0xae, 0x00, 0x87, 0xb3, 0x59, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x8b, 0xbc, 0xff, 0xff, 0xff, 0xd3, 0xe8, 0xf1, 0xd2, 0xe8, 0xf1, 0x39, 0x7f, 0x00, 0xdf, 0xec, 0x90, 0xd2, 0xe7, 0x4a, 0xd2, 0xe7, 0x4e, 0xd1, 0xe6, 0x4d, 0xd8, 0xe8, 0x93, 0x97, 0xc3, 0x00, 0xc7, 0xe0, 0x60, 0x81, 0xb2, 0x00, 0x84, 0xb1, 0x53, 0x19, 0x84, 0xb9, 0x0e, 0x7e, 0xb6, 0x0f, 0x7f, 0xb6, 0x2e, 0x90, 0xc0, 0x29, 0x8e, 0xbf, 0x29, 0x8d, 0xbf, 0x3c, 0x81, 0x00, 0xcf, 0xe7, 0x6b, 0x99, 0xc8, 0x00, 0x99, 0xc8, 0x00, 0x99, 0xc8, 0x00, 0x97, 0xc7, 0x00, 0x98, 0xc8, 0x00, 0x9a, 0xca, 0x00, 0xcd, 0xe6, 0x63, 0x47, 0x8a, 0x00, 0x12, 0x80, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3c, 0x81, 0x00, 0xc0, 0xe7, 0x3a, 0xa1, 0xd7, 0x00, 0xa1, 0xd7, 0x00, 0x9f, 0xd5, 0x00, 0x9c, 0xd0, 0x00, 0x9c, 0xd0, 0x00, 0x9f, 0xd3, 0x00, 0x81, 0xb9, 0x00, 0x74, 0x9f, 0x42, 0x45, 0x96, 0xbd, 0x89, 0xc1, 0xdc, 0xe0, 0xf0, 0xf5, 0xdb, 0xed, 0xf4, 0xdb, 0xed, 0xf4, 0xdb, 0xed, 0xf4, 0x80, 0xae, 0x4c, 0x4a, 0x88, 0x00, 0x4b, 0x89, 0x00, 0x4a, 0x88, 0x00, 0x43, 0x84, 0x00, 0xa2, 0xd9, 0x00, 0xa0, 0xd8, 0x00, 0x80, 0xbc, 0x00, 0x75, 0xa0, 0x46, 0xdd, 0xdd, 0xdd, 0xbf, 0xcd, 0xd5, 0x14, 0x81, 0xb8, 0x0f, 0x7e, 0xb6, 0x0d, 0x7d, 0xb5, 0x0c, 0x7d, 0xb5, 0x0c, 0x7d, 0xb5, 0x14, 0x82, 0xc4, 0x17, 0x84, 0xcb, 0x18, 0x85, 0xd0, 0x14, 0x84, 0xdd, 0x4b, 0x89, 0x00, 0xa6, 0xe4, 0x00, 0x80, 0xbe, 0x00, 0x75, 0xa0, 0x46, 0xde, 0xde, 0xde, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0xf8, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x4f, 0x8b, 0x00, 0x85, 0xc6, 0x00, 0x72, 0x9e, 0x42, 0xde, 0xde, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xdd, 0xdd, 0xdd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static uint8_t* proxScriptAlpha = new uint8_t[256]{ 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00 };

static uint8_t* goScriptRgb = new uint8_t[768]{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x89, 0xbc, 0x3b, 0x97, 0xc4, 0x49, 0x9d, 0xc7, 0x38, 0x95, 0xc3, 0x04, 0x79, 0xb3, 0x07, 0x7a, 0xb4, 0x07, 0x7a, 0xb4, 0x08, 0x7a, 0xb4, 0x0a, 0x7c, 0xb5, 0x0f, 0x7f, 0xb6, 0x14, 0x81, 0xb8, 0xe0, 0xee, 0xf6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x85, 0xbe, 0xda, 0xa7, 0xcf, 0xe4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xba, 0xda, 0xe9, 0xc9, 0xe2, 0xee, 0x4f, 0x9f, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x88, 0xba, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfe, 0xfe, 0xfb, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x41, 0x99, 0xc6, 0xc2, 0xdf, 0xec, 0x34, 0x92, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x9e, 0xc8, 0xff, 0xff, 0xff, 0xf3, 0xf9, 0xfc, 0xf1, 0xf8, 0xfb, 0xf1, 0xf8, 0xfb, 0xf1, 0xf8, 0xfb, 0xf1, 0xf8, 0xfb, 0xf2, 0xf8, 0xfb, 0xf5, 0xfa, 0xfc, 0xff, 0xff, 0xff, 0x01, 0x77, 0xb2, 0x1c, 0x85, 0xba, 0x22, 0x89, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf4, 0xf9, 0xfc, 0x56, 0xa5, 0xcc, 0xff, 0xff, 0xff, 0xeb, 0xf6, 0xf9, 0xea, 0xf5, 0xf9, 0xeb, 0xf5, 0xf9, 0xeb, 0xf5, 0xf9, 0xeb, 0xf5, 0xf9, 0xeb, 0xf5, 0xf9, 0xf5, 0xfa, 0xfc, 0xfd, 0xfe, 0xfe, 0x36, 0x8e, 0xb9, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xce, 0xe4, 0xef, 0x88, 0xbf, 0xdb, 0xff, 0xff, 0xff, 0xe5, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0x00, 0x00, 0x80, 0xc8, 0xe2, 0xee, 0x55, 0x9d, 0xc2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92, 0xc3, 0xda, 0xbb, 0xdb, 0xea, 0xee, 0xf7, 0xfa, 0xdd, 0xee, 0xf5, 0xdd, 0xee, 0xf5, 0xdd, 0xee, 0xf5, 0xdd, 0xee, 0xf5, 0xdd, 0xee, 0xf5, 0xdc, 0xee, 0xf5, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x77, 0xaf, 0xca, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6b, 0xac, 0xcb, 0xcc, 0xe4, 0xf0, 0xe0, 0xef, 0xf6, 0xd6, 0xea, 0xf2, 0xd6, 0xea, 0xf2, 0xd6, 0xea, 0xf2, 0xd6, 0xea, 0xf3, 0xd6, 0xea, 0xf3, 0xd5, 0xea, 0xf3, 0x00, 0x00, 0x80, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x8b, 0xbc, 0xff, 0xff, 0xff, 0xd3, 0xe8, 0xf1, 0xd2, 0xe8, 0xf1, 0xd3, 0xe8, 0xf1, 0xd3, 0xe8, 0xf1, 0xd2, 0xe8, 0xf1, 0xcf, 0xe6, 0xf0, 0xca, 0xe3, 0xee, 0x00, 0x00, 0x80, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x84, 0xb9, 0x0e, 0x7e, 0xb6, 0x0f, 0x7f, 0xb6, 0x2e, 0x90, 0xc0, 0x29, 0x8e, 0xbf, 0x29, 0x8d, 0xbf, 0x29, 0x8e, 0xbf, 0x2b, 0x8e, 0xbf, 0x2d, 0x8f, 0xc0, 0x7c, 0xba, 0xd7, 0xd2, 0xe9, 0xf0, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x80, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb7, 0xd9, 0xe9, 0x1d, 0x86, 0xbb, 0xdc, 0xee, 0xf4, 0x00, 0x00, 0x80, 0x25, 0x87, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x45, 0x96, 0xbd, 0x89, 0xc1, 0xdc, 0xe0, 0xf0, 0xf5, 0xdb, 0xed, 0xf4, 0xdb, 0xed, 0xf4, 0xdb, 0xed, 0xf4, 0xdb, 0xed, 0xf4, 0xdd, 0xef, 0xf5, 0xe3, 0xf2, 0xf7, 0x99, 0xca, 0xdf, 0xea, 0xf4, 0xf8, 0x61, 0xab, 0xcf, 0x71, 0xa9, 0xc4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbf, 0xcd, 0xd5, 0x14, 0x81, 0xb8, 0x0f, 0x7e, 0xb6, 0x0d, 0x7d, 0xb5, 0x0c, 0x7d, 0xb5, 0x0c, 0x7d, 0xb5, 0x0c, 0x7d, 0xb5, 0x0d, 0x7d, 0xb6, 0x0f, 0x7e, 0xb6, 0x11, 0x7f, 0xb7, 0x12, 0x80, 0xb7, 0x26, 0x88, 0xba, 0xe5, 0xe5, 0xe5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xd0, 0xd0, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static uint8_t* goScriptAlpha = new uint8_t[256]{ 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

static uint8_t* saveScriptRgb = new uint8_t[768]{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x7e, 0xb5, 0x3b, 0x97, 0xc4, 0x49, 0x9d, 0xc7, 0x38, 0x95, 0xc3, 0x04, 0x79, 0xb3, 0x07, 0x7a, 0xb4, 0x07, 0x7a, 0xb4, 0x08, 0x7a, 0xb4, 0x0a, 0x7c, 0xb5, 0x0f, 0x7f, 0xb6, 0x14, 0x81, 0xb8, 0x1d, 0x83, 0xbd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x80, 0xb6, 0xa7, 0xcf, 0xe4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xba, 0xda, 0xe9, 0xc9, 0xe2, 0xee, 0x14, 0x7e, 0xb5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x7a, 0xb2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfe, 0xfe, 0xfb, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x41, 0x99, 0xc6, 0xc2, 0xdf, 0xec, 0x35, 0x92, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x9e, 0xc8, 0xff, 0xff, 0xff, 0xf4, 0xfa, 0xfc, 0xf3, 0xf9, 0xfb, 0xf4, 0xfa, 0xfc, 0xf4, 0xfa, 0xfc, 0xf4, 0xfa, 0xfc, 0xf5, 0xfa, 0xfc, 0xf8, 0xfb, 0xfd, 0xff, 0xff, 0xff, 0x02, 0x77, 0xb2, 0x1d, 0x86, 0xba, 0x24, 0x89, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x7f, 0xbf, 0x56, 0xa5, 0xcc, 0xff, 0xff, 0xff, 0xef, 0xf8, 0xfb, 0xf5, 0xfb, 0xfc, 0xfb, 0xfe, 0xfe, 0xfd, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0a, 0x72, 0xa7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x7a, 0xb0, 0x88, 0xbf, 0xdb, 0xff, 0xff, 0xff, 0xf0, 0xf7, 0xfb, 0x57, 0xa5, 0xcb, 0x00, 0x72, 0xae, 0x00, 0x72, 0xae, 0x00, 0x71, 0xae, 0x00, 0x71, 0xae, 0x00, 0x71, 0xaf, 0x00, 0x74, 0xb0, 0x09, 0x7b, 0xb3, 0x13, 0x80, 0xb6, 0x1b, 0x85, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x79, 0xac, 0xbb, 0xdb, 0xea, 0xf1, 0xf8, 0xfa, 0xed, 0xf7, 0xfa, 0x00, 0x73, 0xaf, 0xc6, 0xe8, 0xfd, 0xc1, 0xe4, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xe6, 0xfc, 0xce, 0xec, 0xff, 0x14, 0x81, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x76, 0xa9, 0xcc, 0xe4, 0xf0, 0xe3, 0xf0, 0xf6, 0xe7, 0xf3, 0xf7, 0x00, 0x75, 0xb0, 0xce, 0xe9, 0xfa, 0x02, 0x88, 0xda, 0xec, 0xee, 0xf0, 0xa7, 0xad, 0xb2, 0xa7, 0xad, 0xb2, 0xec, 0xee, 0xf0, 0x02, 0x88, 0xda, 0xd1, 0xea, 0xfb, 0x12, 0x7f, 0xb6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x79, 0xb0, 0xff, 0xff, 0xff, 0xd5, 0xea, 0xf2, 0xe0, 0xf0, 0xf5, 0x01, 0x76, 0xb0, 0xb9, 0xe0, 0xf7, 0x19, 0x94, 0xdd, 0xe9, 0xe9, 0xee, 0xde, 0xe6, 0xef, 0xde, 0xe6, 0xef, 0xe9, 0xe9, 0xee, 0x19, 0x94, 0xdd, 0xbc, 0xe2, 0xf8, 0x12, 0x80, 0xb6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x83, 0xb7, 0xff, 0xff, 0xff, 0xd5, 0xe9, 0xf1, 0xe0, 0xef, 0xf4, 0x04, 0x78, 0xb1, 0xaa, 0xd8, 0xf5, 0x2f, 0x9e, 0xe1, 0xa1, 0xca, 0xe7, 0xe0, 0xe2, 0xeb, 0xe0, 0xe2, 0xeb, 0xa1, 0xca, 0xe7, 0x2f, 0x9e, 0xe1, 0xad, 0xd9, 0xf6, 0x14, 0x80, 0xb6, 0x19, 0x84, 0xb9, 0x0e, 0x7e, 0xb6, 0x0f, 0x7f, 0xb6, 0x2e, 0x90, 0xc0, 0x2b, 0x8f, 0xbf, 0x34, 0x93, 0xc2, 0x07, 0x79, 0xb2, 0x9d, 0xd3, 0xf4, 0x41, 0xa6, 0xe4, 0x3a, 0xa4, 0xe3, 0x33, 0xa1, 0xe3, 0x32, 0xa1, 0xe2, 0x3a, 0xa4, 0xe3, 0x41, 0xa6, 0xe3, 0x9e, 0xd4, 0xf4, 0x14, 0x81, 0xb6, 0x12, 0x80, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x05, 0x78, 0xb1, 0x91, 0xcd, 0xf2, 0x4f, 0xad, 0xe6, 0xa9, 0xcf, 0xea, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xa7, 0xce, 0xe8, 0x4e, 0xad, 0xe6, 0x93, 0xce, 0xf3, 0x15, 0x81, 0xb6, 0x14, 0x7a, 0xab, 0x89, 0xc1, 0xdc, 0xe0, 0xf0, 0xf5, 0xdb, 0xed, 0xf4, 0xdd, 0xee, 0xf5, 0xe6, 0xf4, 0xf7, 0x08, 0x7a, 0xb2, 0x89, 0xca, 0xf3, 0x5c, 0xb6, 0xeb, 0xed, 0xed, 0xf2, 0x78, 0x79, 0x7f, 0xe2, 0xe9, 0xf1, 0xe9, 0xe9, 0xee, 0x5b, 0xb5, 0xea, 0x8b, 0xcc, 0xf3, 0x16, 0x81, 0xb6, 0x0f, 0x43, 0x61, 0x14, 0x81, 0xb8, 0x0f, 0x7e, 0xb6, 0x0d, 0x7d, 0xb5, 0x0d, 0x7d, 0xb6, 0x10, 0x7f, 0xb6, 0x13, 0x80, 0xb6, 0x8b, 0xcc, 0xf6, 0x75, 0xc2, 0xf3, 0xff, 0xfc, 0xf9, 0x91, 0x8d, 0x8b, 0xf9, 0xf9, 0xf9, 0xfc, 0xf8, 0xf4, 0x74, 0xc1, 0xf2, 0x8b, 0xcd, 0xf6, 0x18, 0x82, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x79, 0xa8, 0x18, 0x82, 0xb7, 0x14, 0x81, 0xb6, 0x10, 0x80, 0xb8, 0x0f, 0x81, 0xb9, 0x0e, 0x7f, 0xb8, 0x0f, 0x7e, 0xb6, 0x13, 0x80, 0xb6, 0x18, 0x82, 0xb7, 0x1c, 0x82, 0xb7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static uint8_t* saveScriptAlpha = new uint8_t[256]{ 0x00, 0x00, 0x00, 0x00, 0xea, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x23, 0x00, 0x00, 0x00, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x00, 0x00, 0x00, 0xe5, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x0c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc6, 0x33, 0x33, 0x00, 0x00, 0x34, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xeb, 0x00, 0x00, 0x73, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x9b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xd2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xca, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x44, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x33, 0x33, 0x33, 0x33, 0x33, 0xb9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x30 };

static uint8_t* insertScriptRgb = new uint8_t[768]{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x7e, 0xb5, 0x3b, 0x97, 0xc4, 0x49, 0x9d, 0xc7, 0x38, 0x95, 0xc3, 0x04, 0x79, 0xb3, 0x07, 0x7a, 0xb4, 0x07, 0x7a, 0xb4, 0x08, 0x7a, 0xb4, 0x0a, 0x7c, 0xb5, 0x0f, 0x7f, 0xb6, 0x14, 0x81, 0xb8, 0x1d, 0x83, 0xbd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x80, 0xb6, 0xa7, 0xcf, 0xe4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xba, 0xda, 0xe9, 0xc9, 0xe2, 0xee, 0x14, 0x7e, 0xb5, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x7a, 0xb2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xfe, 0xfe, 0xfb, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfc, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0x40, 0x99, 0xc7, 0xc0, 0xdf, 0xed, 0x32, 0x92, 0xc2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x9e, 0xc8, 0xff, 0xff, 0xff, 0xf3, 0xf9, 0xfc, 0xf1, 0xf8, 0xfb, 0xf1, 0xf8, 0xfb, 0xf1, 0xf8, 0xfb, 0xf1, 0xf8, 0xfc, 0xf2, 0xf9, 0xfd, 0xf5, 0xfb, 0xfe, 0xff, 0xff, 0xff, 0x00, 0x77, 0xb6, 0x0e, 0x84, 0xc2, 0x10, 0x87, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x7f, 0xbf, 0x56, 0xa5, 0xcc, 0xff, 0xff, 0xff, 0xeb, 0xf6, 0xf9, 0xea, 0xf5, 0xf9, 0xeb, 0xf5, 0xf9, 0xeb, 0xf6, 0xfb, 0xeb, 0xf8, 0xff, 0xeb, 0xfb, 0xff, 0xf4, 0xff, 0xff, 0xf5, 0xff, 0xff, 0x00, 0x70, 0xb6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x7a, 0xb0, 0x88, 0xbf, 0xdb, 0xff, 0xff, 0xff, 0xe5, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf1, 0xf7, 0xe4, 0xf3, 0xfc, 0xe2, 0xe3, 0xde, 0xd8, 0x8e, 0x37, 0xd8, 0x8f, 0x3c, 0xdc, 0x92, 0x3f, 0xe2, 0x98, 0x45, 0xe1, 0x9d, 0x4d, 0xdf, 0x9e, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x79, 0xac, 0xbb, 0xdb, 0xea, 0xee, 0xf7, 0xfa, 0xdd, 0xee, 0xf5, 0xdd, 0xee, 0xf5, 0xdd, 0xef, 0xf6, 0xdd, 0xf2, 0xfd, 0xdb, 0xcf, 0xb9, 0xdd, 0x9e, 0x39, 0xf9, 0xe8, 0x8f, 0xf9, 0xe8, 0x92, 0xfb, 0xe9, 0x97, 0xd8, 0x98, 0x4c, 0x9f, 0x72, 0x3b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x76, 0xa9, 0xcc, 0xe4, 0xf0, 0xe0, 0xef, 0xf6, 0xd6, 0xea, 0xf2, 0xd6, 0xea, 0xf2, 0xd6, 0xeb, 0xf4, 0xd6, 0xef, 0xfe, 0xd5, 0xb8, 0x8f, 0xe6, 0xb5, 0x55, 0xfe, 0xf9, 0xd9, 0xf4, 0xd3, 0x4d, 0xe5, 0xb5, 0x4b, 0xd4, 0x95, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x79, 0xb0, 0xff, 0xff, 0xff, 0xd2, 0xe9, 0xf1, 0xd1, 0xe8, 0xf0, 0xd1, 0xe8, 0xf1, 0xd1, 0xe9, 0xf3, 0xcf, 0xee, 0xfe, 0xd2, 0xa3, 0x64, 0xf2, 0xd4, 0x88, 0xf8, 0xe0, 0x7c, 0xef, 0xcc, 0x58, 0xd5, 0x95, 0x45, 0x8c, 0x63, 0x2e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x83, 0xb7, 0xff, 0xff, 0xff, 0xd3, 0xe8, 0xf1, 0xd2, 0xe8, 0xf1, 0xd3, 0xe8, 0xf1, 0xd3, 0xe9, 0xf3, 0xd0, 0xee, 0xff, 0xd8, 0x89, 0x2c, 0xff, 0xec, 0x8b, 0xf9, 0xe1, 0x6c, 0xe8, 0xc0, 0x5c, 0xd0, 0x8c, 0x3f, 0xd3, 0x92, 0x43, 0xd5, 0x95, 0x45, 0x19, 0x84, 0xb9, 0x0e, 0x7e, 0xb6, 0x0f, 0x7f, 0xb6, 0x2e, 0x90, 0xc0, 0x29, 0x8e, 0xbf, 0x29, 0x8d, 0xbf, 0x29, 0x8e, 0xbf, 0x2a, 0x8f, 0xc1, 0x29, 0x94, 0xcc, 0xe0, 0x8c, 0x25, 0xdf, 0xa1, 0x40, 0xe1, 0xaf, 0x50, 0xfd, 0xe9, 0x7d, 0xff, 0xef, 0x81, 0xe3, 0xb4, 0x57, 0xc1, 0x86, 0x39, 0x12, 0x80, 0xb7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb5, 0xdb, 0xef, 0x17, 0x8d, 0xd0, 0xc9, 0xb9, 0x9c, 0xf2, 0xcf, 0x6d, 0xfd, 0xea, 0x87, 0xd6, 0x9d, 0x45, 0xad, 0x76, 0x30, 0x00, 0x00, 0x00, 0x14, 0x7a, 0xab, 0x89, 0xc1, 0xdc, 0xe0, 0xf0, 0xf5, 0xdb, 0xed, 0xf4, 0xdb, 0xed, 0xf4, 0xdb, 0xed, 0xf4, 0xdb, 0xed, 0xf4, 0xdd, 0xef, 0xf5, 0xe0, 0xf2, 0xfc, 0x8f, 0xc6, 0xe3, 0xd6, 0xa4, 0x4a, 0xff, 0xf4, 0x95, 0xd7, 0x9d, 0x46, 0x96, 0x66, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x43, 0x61, 0x14, 0x81, 0xb8, 0x0f, 0x7e, 0xb6, 0x0d, 0x7d, 0xb5, 0x0c, 0x7d, 0xb5, 0x0c, 0x7d, 0xb5, 0x0c, 0x7d, 0xb5, 0x0c, 0x7d, 0xb7, 0x05, 0x7e, 0xbe, 0x6d, 0x85, 0x75, 0xdc, 0x9a, 0x39, 0xd5, 0x99, 0x3f, 0x50, 0x34, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe2, 0x8c, 0x20, 0xcd, 0x8a, 0x2b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static uint8_t* insertScriptAlpha = new uint8_t[256]{ 0x00, 0x00, 0x00, 0x00, 0xea, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x23, 0x00, 0x00, 0x00, 0x83, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x00, 0x00, 0x00, 0xe5, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x0c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc6, 0x33, 0x33, 0x00, 0x00, 0x34, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x73, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7d, 0x00, 0x00, 0x9b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf5, 0x12, 0x00, 0x00, 0xd2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x69, 0x00, 0x00, 0x00, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x99, 0x23, 0xca, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7a, 0x1a, 0x00, 0x44, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x49, 0x12, 0x00, 0x00, 0x07, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xff, 0xee, 0x33, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00 };

EditorFrame::EditorFrame(const wxString& type, Editor* editor) : wxFrame(nullptr, wxID_ANY, type + L" Editor"), m_pEditor(editor), m_Type(type)
{

}

void EditorFrame::CreateMyToolBar()
{
	CreateToolBar(wxTB_DEFAULT_STYLE, wxID_ANY);
	m_pToolBar = GetToolBar();
	m_pToolBar->SetMargins(2, 2);	
	
	Bind(wxEVT_TOOL, &EditorFrame::OnPrevFileClick, this, m_pToolBar->AddTool(wxNewId(), L"Previous script", wxImage(16, 16, prevScriptRgb, prevScriptAlpha, true), "Previous script")->GetId());
	Bind(wxEVT_TOOL, &EditorFrame::OnProxFileClick, this, m_pToolBar->AddTool(wxNewId(), L"Following script", wxImage(16, 16, proxScriptRgb, proxScriptAlpha, true), "Following script")->GetId());
	Bind(wxEVT_TOOL, &EditorFrame::OnGoFileClick, this, m_pToolBar->AddTool(wxNewId(), L"Got to script", wxImage(16, 16, goScriptRgb, goScriptAlpha, true), "Go to script")->GetId());
	Bind(wxEVT_TOOL, &EditorFrame::OnSaveFileClick, this, m_pToolBar->AddTool(wxNewId(), L"Save the script", wxImage(16, 16, saveScriptRgb, saveScriptAlpha, true), "Save the script")->GetId());
	Bind(wxEVT_TOOL, &EditorFrame::OnInsertFileClick, this, m_pToolBar->AddTool(wxNewId(), L"Insert script", wxImage(16, 16, insertScriptRgb, insertScriptAlpha, true), "Insert script")->GetId());

	m_pToolBar->Realize();	
}

void EditorFrame::CreateMyMenuBar()
{
	if (m_pMenuBar)
		return;

	m_pMenuBar = new wxMenuBar();
	SetMenuBar(m_pMenuBar);
}

void EditorFrame::CreateSearchMenu()
{
	CreateMyMenuBar();

	m_pMenuSearch = new wxMenu();
	m_pMenuSearch->Bind(wxEVT_MENU, &EditorFrame::OnFindTextClick, this, m_pMenuSearch->Append(wxID_FIND, L"Find Text\tCtrl-F")->GetId());
	m_pMenuSearch->Bind(wxEVT_MENU, &EditorFrame::OnFindNextClick, this, m_pMenuSearch->Append(wxNewId(), L"Find Next\tF3")->GetId());

	m_pMenuBar->Append(m_pMenuSearch, L"Find");
}

void EditorFrame::CreateToolsMenu()
{
	CreateMyMenuBar();

	m_pMenuTools = new wxMenu();

	m_pMenuTools->Bind(wxEVT_MENU, &EditorFrame::OnRemoveSpacesClick, this, m_pMenuTools->Append(wxNewId(), "Remove Padding Spaces", nullptr, "Removes spaces after line end")->GetId());

	m_pMenuBar->Append(m_pMenuTools, L"Tools");
}

void EditorFrame::CreateMyStatusBar(size_t count)
{
	m_pStatusBar = CreateStatusBar(count);	
}

void EditorFrame::UpdateIndex()
{
	m_pStatusBar->SetStatusText(wxString(L"Index: ") << m_pEditor->GetIndex() << L"/" << m_pEditor->GetCount(), 0);
}

void EditorFrame::OnPrevFile()
{	
	if (m_pEditor->PreviousFile())
		UpdateText();
}

void EditorFrame::OnProxFile()
{
	if (m_pEditor->NextFile())
		UpdateText();
}

void EditorFrame::SetIndex(size_t index)
{
	m_pEditor->SetIndex(index);
	UpdateText();
}

void EditorFrame::OnGoFile()
{
	wxTextEntryDialog dialog(nullptr, L"Choose a number");
	dialog.SetTextValidator(wxFILTER_NUMERIC);

	if (dialog.ShowModal() != wxID_CANCEL)
	{
		uint32_t number = std::stoi(dialog.GetValue().ToStdString());
		if (m_pEditor->Open(number))
		{
			UpdateText();
		}
	}
}

void EditorFrame::RemovePaddingSpaces()
{
	
}

void EditorFrame::OnSaveFile()
{
	m_pEditor->SaveFile();
}

void EditorFrame::OnInsertFile()
{
	m_pEditor->Insert();
}

void EditorFrame::OnFindText()
{
	FrameSearchScript dialog;

	if (!m_pEditor->IsOpened())
		dialog.InScript(true);

	if (m_pEditor->GetRom(true).Console == console::DS)
	{
		dialog.SetEol("\\n", "\n");
	}
	else
	{
		dialog.SetEol("\\r\\n", "\r\n");
	}

	if (dialog.ShowModal() != wxID_CANCEL)
	{
		wxString search = dialog.GetSearch();
		wxString replace = dialog.GetReplace();
		bool inScript = dialog.InScript();
		bool extended = dialog.Extended();
		bool translated = dialog.Translated();
		bool find = dialog.Find();
		bool useTable = dialog.UseTable();

		if (find)
		{
			if (!inScript)
			{
				FindText(search, useTable, translated);
			}
			else
			{
				//ShowResultWindow(m_Editor.FindInScripts(search, useTable, translated));
			}
		}
		else
		{
			if (!inScript)
			{
				ReplaceTxt(search, replace, useTable);				

				//m_FindPos.clear();
				m_FindIndex = 0;
			}
			else
			{
				wxMessageBox("Replace in script is not yet supported in this version.", "Huh?", wxICON_WARNING);
			}
		}
	}

	//Layout();
}

void EditorFrame::FindText(const wxString& search, bool useTable, bool translated)
{	
	m_FindPositions = m_pEditor->Find(search.ToStdString(), useTable, translated);
	m_FindIndex = 0;

	if (!m_FindPositions.empty())
		m_pEditor->SetIndex(m_FindPositions[m_FindIndex]);
}

void EditorFrame::ReplaceTxt(const wxString& search, const wxString& replace, bool useTable)
{
	UpdateText();
}

void EditorFrame::OnPrevFileClick(wxCommandEvent& event)
{
	OnPrevFile();
	event.Skip();
}

void EditorFrame::OnProxFileClick(wxCommandEvent& event)
{
	OnProxFile();
	event.Skip();
}

void EditorFrame::OnGoFileClick(wxCommandEvent& event)
{
	OnGoFile();
	event.Skip();
}

void EditorFrame::OnSaveFileClick(wxCommandEvent& event)
{
	OnSaveFile();
	event.Skip();
}

void EditorFrame::OnInsertFileClick(wxCommandEvent& event)
{
	OnInsertFile();
	event.Skip();
}

void EditorFrame::OnFindTextClick(wxCommandEvent& event)
{
	OnFindText();
	event.Skip();
}

void EditorFrame::OnFindNextClick(wxCommandEvent& event)
{
	OnFindNext();
	event.Skip();
}

void EditorFrame::OnRemoveSpacesClick(wxCommandEvent& event)
{
	RemovePaddingSpaces();
	event.Skip();
}