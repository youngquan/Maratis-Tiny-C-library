/*======================================================================
 Maratis Tiny C Library
 version 1.0
------------------------------------------------------------------------
 Copyright (c) 2015 Anael Seghezzi <www.maratis3d.com>

 This software is provided 'as-is', without any express or implied
 warranty. In no event will the authors be held liable for any damages
 arising from the use of this software.

 Permission is granted to anyone to use this software for any purpose,
 including commercial applications, and to alter it and redistribute it
 freely, subject to the following restrictions:

 1. The origin of this software must not be misrepresented; you must not
    claim that you wrote the original software. If you use this software
    in a product, an acknowledgment in the product documentation would
    be appreciated but is not required.

 2. Altered source versions must be plainly marked as such, and must not
    be misrepresented as being the original software.

 3. This notice may not be removed or altered from any source
    distribution.

========================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>

#include <m_image.h>
#include "m_half.c"

/*
for (i = 0; i < 4096; i++)
	_src[i] = ((float)i + 0.5f) / 4095.0f;	
m_color_linear_to_sRGB(_src, _dst, 4096);
for (i = 0; i < 4096; i++)
	_m_srgb_table[i] = (int)(_dst[i] * 255.0f + 0.5f);
*/
static unsigned char _m_srgb_table[4096] = {
0, 1, 2, 3, 4, 4, 5, 6, 7, 8, 8, 9, 10, 11, 12, 12, 13, 14, 14, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 
22, 22, 23, 23, 24, 24, 24, 25, 25, 26, 26, 26, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 31, 32, 32, 32, 33, 33, 33, 
34, 34, 34, 35, 35, 35, 35, 36, 36, 36, 37, 37, 37, 37, 38, 38, 38, 39, 39, 39, 39, 40, 40, 40, 40, 41, 41, 41, 41, 42, 42, 42, 
42, 43, 43, 43, 43, 44, 44, 44, 44, 45, 45, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 47, 47, 48, 48, 48, 48, 49, 49, 49, 49, 49, 
50, 50, 50, 50, 50, 51, 51, 51, 51, 51, 52, 52, 52, 52, 52, 53, 53, 53, 53, 53, 54, 54, 54, 54, 54, 54, 55, 55, 55, 55, 55, 56, 
56, 56, 56, 56, 56, 57, 57, 57, 57, 57, 58, 58, 58, 58, 58, 58, 59, 59, 59, 59, 59, 59, 60, 60, 60, 60, 60, 60, 61, 61, 61, 61, 
61, 61, 62, 62, 62, 62, 62, 62, 63, 63, 63, 63, 63, 63, 63, 64, 64, 64, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 66, 66, 66, 66, 
66, 66, 67, 67, 67, 67, 67, 67, 67, 68, 68, 68, 68, 68, 68, 68, 69, 69, 69, 69, 69, 69, 69, 70, 70, 70, 70, 70, 70, 70, 71, 71, 
71, 71, 71, 71, 71, 71, 72, 72, 72, 72, 72, 72, 72, 73, 73, 73, 73, 73, 73, 73, 73, 74, 74, 74, 74, 74, 74, 74, 75, 75, 75, 75, 
75, 75, 75, 75, 76, 76, 76, 76, 76, 76, 76, 76, 77, 77, 77, 77, 77, 77, 77, 77, 78, 78, 78, 78, 78, 78, 78, 78, 79, 79, 79, 79, 
79, 79, 79, 79, 80, 80, 80, 80, 80, 80, 80, 80, 80, 81, 81, 81, 81, 81, 81, 81, 81, 82, 82, 82, 82, 82, 82, 82, 82, 82, 83, 83, 
83, 83, 83, 83, 83, 83, 83, 84, 84, 84, 84, 84, 84, 84, 84, 84, 85, 85, 85, 85, 85, 85, 85, 85, 85, 86, 86, 86, 86, 86, 86, 86, 
86, 86, 87, 87, 87, 87, 87, 87, 87, 87, 87, 88, 88, 88, 88, 88, 88, 88, 88, 88, 89, 89, 89, 89, 89, 89, 89, 89, 89, 89, 90, 90, 
90, 90, 90, 90, 90, 90, 90, 90, 91, 91, 91, 91, 91, 91, 91, 91, 91, 92, 92, 92, 92, 92, 92, 92, 92, 92, 92, 93, 93, 93, 93, 93, 
93, 93, 93, 93, 93, 94, 94, 94, 94, 94, 94, 94, 94, 94, 94, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 95, 96, 96, 96, 96, 96, 96, 
96, 96, 96, 96, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 97, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 98, 99, 99, 99, 99, 99, 99, 
99, 99, 99, 99, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 102, 102, 102, 102, 102, 102, 
102, 102, 102, 102, 102, 102, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 105, 105, 105, 
105, 105, 105, 105, 105, 105, 105, 105, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 
108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 110, 110, 110, 110, 110, 110, 110, 110, 
110, 110, 110, 110, 110, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 113, 113, 
113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 115, 115, 115, 115, 115, 115, 115, 115, 
115, 115, 115, 115, 115, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 118, 
118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 120, 120, 120, 120, 120, 120, 
120, 120, 120, 120, 120, 120, 120, 120, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 121, 122, 122, 122, 122, 122, 122, 122, 122, 122, 122, 
122, 122, 122, 122, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 123, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 124, 
124, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 127, 127, 
127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 129, 129, 129, 129, 129, 
129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 129, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 130, 131, 131, 131, 131, 131, 131, 
131, 131, 131, 131, 131, 131, 131, 131, 131, 132, 132, 132, 132, 132, 132, 132, 132, 132, 132, 132, 132, 132, 132, 132, 132, 133, 133, 133, 133, 133, 133, 133, 
133, 133, 133, 133, 133, 133, 133, 133, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 134, 135, 135, 135, 135, 135, 135, 135, 135, 
135, 135, 135, 135, 135, 135, 135, 135, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 136, 137, 137, 137, 137, 137, 137, 137, 137, 
137, 137, 137, 137, 137, 137, 137, 137, 137, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 139, 139, 139, 139, 139, 139, 139, 
139, 139, 139, 139, 139, 139, 139, 139, 139, 139, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 141, 141, 141, 141, 141, 141, 
141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 141, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 143, 143, 143, 143, 
143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 143, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 145, 
145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 145, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 146, 
146, 146, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 147, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 148, 
148, 148, 148, 148, 148, 148, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 150, 150, 150, 150, 150, 150, 150, 150, 
150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 152, 152, 152, 
152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 152, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 153, 
153, 153, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 155, 
155, 155, 155, 155, 155, 155, 155, 155, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 156, 157, 157, 157, 157, 157, 
157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 157, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 158, 
158, 158, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 159, 160, 160, 160, 160, 160, 160, 160, 160, 160, 160, 
160, 160, 160, 160, 160, 160, 160, 160, 160, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 161, 162, 162, 162, 
162, 162, 162, 162, 162, 162, 162, 162, 162, 162, 162, 162, 162, 162, 162, 162, 162, 162, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 163, 
163, 163, 163, 163, 163, 163, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 164, 165, 165, 165, 165, 165, 165, 
165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 165, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 166, 
166, 166, 166, 166, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 167, 168, 168, 168, 168, 168, 168, 168, 
168, 168, 168, 168, 168, 168, 168, 168, 168, 168, 168, 168, 168, 168, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 
169, 169, 169, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 170, 171, 171, 171, 171, 171, 171, 171, 
171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 171, 172, 172, 172, 172, 172, 172, 172, 172, 172, 172, 172, 172, 172, 172, 172, 172, 172, 172, 
172, 172, 172, 172, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 173, 174, 174, 174, 174, 174, 174, 
174, 174, 174, 174, 174, 174, 174, 174, 174, 174, 174, 174, 174, 174, 174, 174, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 175, 
175, 175, 175, 175, 175, 175, 175, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 176, 177, 177, 177, 
177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 177, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 
178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 179, 
179, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 180, 181, 181, 181, 181, 181, 181, 181, 
181, 181, 181, 181, 181, 181, 181, 181, 181, 181, 181, 181, 181, 181, 181, 181, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 182, 
182, 182, 182, 182, 182, 182, 182, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 183, 184, 
184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 184, 185, 185, 185, 185, 185, 185, 185, 185, 185, 
185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 185, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 186, 
186, 186, 186, 186, 186, 186, 186, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 187, 188, 
188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 188, 189, 189, 189, 189, 189, 189, 189, 189, 
189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 189, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 190, 
190, 190, 190, 190, 190, 190, 190, 190, 190, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 191, 
191, 191, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 193, 193, 193, 193, 193, 
193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 193, 194, 194, 194, 194, 194, 194, 194, 194, 194, 194, 194, 194, 
194, 194, 194, 194, 194, 194, 194, 194, 194, 194, 194, 194, 194, 194, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 195, 
195, 195, 195, 195, 195, 195, 195, 195, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 196, 
196, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 197, 198, 198, 198, 198, 198, 
198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 198, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 
199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 199, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 
200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 201, 
201, 201, 201, 201, 201, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 202, 
203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 203, 204, 204, 204, 204, 204, 
204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 204, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 
205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 
206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 206, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 207, 
207, 207, 207, 207, 207, 207, 207, 207, 207, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 208, 
208, 208, 208, 208, 208, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 209, 
209, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 210, 211, 211, 211, 
211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 211, 212, 212, 212, 212, 212, 212, 
212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 212, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 
213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 213, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 
214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 214, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 
215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 215, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 
216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 216, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 217, 
217, 217, 217, 217, 217, 217, 217, 217, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 218, 
218, 218, 218, 218, 218, 218, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 
219, 219, 219, 219, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 
220, 220, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 221, 
222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 222, 223, 223, 
223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 223, 224, 224, 224, 
224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 225, 225, 225, 225, 
225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 225, 226, 226, 226, 226, 226, 
226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 226, 227, 227, 227, 227, 227, 227, 
227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 227, 228, 228, 228, 228, 228, 228, 228, 
228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 228, 229, 229, 229, 229, 229, 229, 229, 
229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 229, 230, 230, 230, 230, 230, 230, 230, 230, 
230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 230, 231, 231, 231, 231, 231, 231, 231, 231, 
231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 231, 232, 232, 232, 232, 232, 232, 232, 232, 
232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 232, 233, 233, 233, 233, 233, 233, 233, 
233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 233, 234, 234, 234, 234, 234, 234, 234, 
234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 234, 235, 235, 235, 235, 235, 235, 
235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 235, 236, 236, 236, 236, 236, 236, 
236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 236, 237, 237, 237, 237, 237, 
237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 238, 238, 238, 
238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 238, 239, 239, 
239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 239, 240, 
240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 240, 
240, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 241, 
241, 241, 241, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 242, 
242, 242, 242, 242, 242, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 243, 
243, 243, 243, 243, 243, 243, 243, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 
244, 244, 244, 244, 244, 244, 244, 244, 244, 244, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 
245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 245, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 
246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 
247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 
248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 
249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 250, 250, 250, 250, 250, 250, 250, 
250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 251, 251, 251, 
251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 251, 
252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 252, 
252, 252, 252, 252, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 253, 
253, 253, 253, 253, 253, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 
254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255
};

void m_image_create(struct m_image *image, char type, int width, int height, int comp)
{
	int size = width * height * comp;
	assert(size > 0);

	/* already allocated */
	if (image->data != 0 && type == image->type && width == image->width && height == image->height && comp == image->comp)
		return;

	M_SAFE_FREE(image->data);

	switch (type) {
	case M_BYTE:
	case M_UBYTE:
		image->data = malloc(size * sizeof(char));
		break;
	case M_SHORT:
	case M_USHORT:
	case M_HALF:
		image->data = malloc(size * sizeof(short));
		break;
	case M_INT:
	case M_UINT:
		image->data = malloc(size * sizeof(int));
		break;
	case M_FLOAT:
		image->data = malloc(size * sizeof(float));
		break;
	default:
		assert(0);
		return;
	}

	image->type = type;
	image->width = width;
	image->height = height;
	image->comp = comp;
	image->size = size;
}

void m_image_destroy(struct m_image *image)
{
	M_SAFE_FREE(image->data);
	memset(image, 0, sizeof(struct m_image));
}

void m_image_copy(struct m_image *dest, const struct m_image *src)
{
	m_image_create(dest, src->type, src->width, src->height, src->comp);
	
	switch (dest->type) {
	case M_BYTE:
	case M_UBYTE:
		memcpy(dest->data, src->data, dest->size*sizeof(char));
		break;
	case M_SHORT:
	case M_USHORT:
	case M_HALF:
		memcpy(dest->data, src->data, dest->size*sizeof(short));
		break;
	case M_INT:
	case M_UINT:
		memcpy(dest->data, src->data, dest->size*sizeof(int));
		break;
	case M_FLOAT:
		memcpy(dest->data, src->data, dest->size*sizeof(float));
		break;
	default:
		assert(0);
		break;
	}
}

void m_image_copy_sub_image(struct m_image *dest, const struct m_image *src, int x, int y, int w, int h)
{
	#define COPY_SUBI(T)\
	{\
		T *sData = (T *)src->data + (M_MINy * src->width + M_MINx) * comp;\
		T *dData = (T *)dest->data;\
		int y;\
		for (y = M_MINy; y <= M_MAXy; y++) {\
			memcpy(dData, sData, dstep * sizeof(T));\
			dData += dstep;\
			sData += sstep;\
		}\
	}

	int comp = src->comp;
	int M_MINx = M_MAX(0, x);
	int M_MINy = M_MAX(0, y);
	int M_MAXx = M_CLAMP(x + w - 1, 0, src->width - 1);
	int M_MAXy = M_CLAMP(y + h - 1, 0, src->height - 1);
	int dwidth = 1 + M_MAXx - M_MINx;
	int dheight = 1 + M_MAXy - M_MINy;
	int sstep = src->width * comp;
	int dstep = dwidth * comp;

	m_image_create(dest, src->type, dwidth, dheight, src->comp);
	
	switch(src->type)
	{
	case M_BYTE:
	case M_UBYTE:
		COPY_SUBI(char);
		break;
	case M_SHORT:
	case M_USHORT:
	case M_HALF:
		COPY_SUBI(short);
		break;
	case M_INT:
	case M_UINT:
		COPY_SUBI(int);
		break;
	case M_FLOAT:
		COPY_SUBI(float);
		break;
	default:
		assert(0);
		break;
	}
}

void m_image_ubyte_to_float(struct m_image *dest, const struct m_image *src)
{
	unsigned char *src_data;
	float *dest_data;
	float ubyte_div = 1.0f / 255.0f;
	int i;

	m_image_create(dest, M_FLOAT, src->width, src->height, src->comp);

	src_data = (unsigned char *)src->data;
	dest_data = (float *)dest->data;
	for (i = 0; i < src->size; i++)
		dest_data[i] = (float)src_data[i] * ubyte_div;
}

void m_image_ushort_to_float(struct m_image *dest, const struct m_image *src)
{
	unsigned short *src_data;
	float *dest_data;
	float ushort_div = 1.0f / (float)65535;
	int i;

	m_image_create(dest, M_FLOAT, src->width, src->height, src->comp);

	src_data = (unsigned short *)src->data;
	dest_data = (float *)dest->data;
	for (i = 0; i < src->size; i++)
		dest_data[i] = (float)src_data[i] * ushort_div;
}

void m_image_half_to_float(struct m_image *dest, const struct m_image *src)
{
	uint16_t *src_data;
	float *dest_data;
	int i;

	m_image_create(dest, M_FLOAT, src->width, src->height, src->comp);

	src_data = (uint16_t *)src->data;
	dest_data = (float *)dest->data;
	for (i = 0; i < src->size; i++)
		dest_data[i] = m_half2float(src_data[i]);
}

void m_image_float_to_ubyte(struct m_image *dest, const struct m_image *src)
{
	float *src_data;
	unsigned char *dest_data;
	int i;

	m_image_create(dest, M_UBYTE, src->width, src->height, src->comp);

	src_data = (float *)src->data;
	dest_data = (unsigned char *)dest->data;
	for (i = 0; i < src->size; i++) {
		int x = (int)(src_data[i] * 255);
		dest_data[i] = (unsigned char)M_CLAMP(x, 0, 255);
	}
}

void m_image_float_to_ushort(struct m_image *dest, const struct m_image *src)
{
	float *src_data;
	unsigned short *dest_data;
	int i;

	m_image_create(dest, M_USHORT, src->width, src->height, src->comp);

	src_data = (float *)src->data;
	dest_data = (unsigned short *)dest->data;
	for (i = 0; i < src->size; i++) {
		int x = (int)(src_data[i] * 65535);
		dest_data[i] = (unsigned short)M_CLAMP(x, 0, 65535);
	}
}

void m_image_float_to_half(struct m_image *dest, const struct m_image *src)
{
	float *src_data;
	uint16_t *dest_data;
	int i;

	m_image_create(dest, M_USHORT, src->width, src->height, src->comp);

	src_data = (float *)src->data;
	dest_data = (uint16_t *)dest->data;
	for (i = 0; i < src->size; i++)
		dest_data[i] = m_float2half(src_data[i]);
}

void m_image_float_to_srgb(struct m_image *dest, const struct m_image *src)
{
	float *src_data;
	unsigned char *dest_data;
	int i;

	m_image_create(dest, M_UBYTE, src->width, src->height, src->comp);

	src_data = (float *)src->data;
	dest_data = (unsigned char *)dest->data;
	for (i = 0; i < src->size; i++) {
		float f = M_CLAMP(src_data[i], 0, 1);
		short x = (short)(f * 4095);
		dest_data[i] = _m_srgb_table[x];
	}
}

void m_image_extract_component(struct m_image *dest, const struct m_image *src, int c)
{
	#define EXTRACT(T)\
	{\
		T *dest_pixel = (T *)dest->data;\
		T *src_pixel = (T *)src->data;\
		for (i = 0; i < size; i += comp) {\
			(*dest_pixel) = src_pixel[c];\
			dest_pixel++;\
			src_pixel += comp;\
		}\
	}

	int width = src->width;
	int height = src->height;
	int comp = src->comp;
	int size = src->size;
	int i;

	if(c >= src->comp) {
		assert(0);
		return;
	}

	m_image_create(dest, src->type, width, height, 1);

	switch(src->type)
	{
	case M_BYTE:
	case M_UBYTE:
		EXTRACT(char);
		break;
	case M_SHORT:
	case M_USHORT:
	case M_HALF:
		EXTRACT(short);
		break;
	case M_INT:
	case M_UINT:
		EXTRACT(int);
		break;
	case M_FLOAT:
		EXTRACT(float);
		break;
	default:
		assert(0);
		break;
	}
}

void m_image_reframe(struct m_image *dest, const struct m_image *src, int left, int top, int right, int bottom)
{
	#define REFRAME(T)\
	{\
		T *src_data;\
		T *src_pixel;\
		T *dest_pixel;\
		int c;\
		int x, y;\
		m_image_create(dest, src->type, width2, height2, comp);\
		src_data = (T *)src->data;\
		dest_pixel = (T *)dest->data;\
		for (y = 0; y < height2; y++) {\
			T *src_y;\
			int ys = y - top;\
			src_y = src_data + M_CLAMP(ys, 0, hm1) * width * comp;\
			for (x = 0; x < width2; x++) {\
				int xs = x - left;\
				src_pixel = src_y + M_CLAMP(xs, 0, wm1) * comp;\
				for (c = 0; c < comp; c++)\
					dest_pixel[c] = src_pixel[c];\
				dest_pixel += comp;\
			}\
		}\
	}

	if(left != 0 || top != 0 || right != 0 || bottom != 0) {

		int comp = src->comp;
		int width = src->width;
		int height = src->height;
		int width2 = width + left + right;
		int height2 = height + top + bottom;
		int wm1 = width - 1;
		int hm1 = height - 1;

		if(width2 > 0 && height2 > 0) {

			switch(src->type) {
			case M_BYTE:
			case M_UBYTE:
				REFRAME(char);
				break;
			case M_SHORT:
			case M_USHORT:
			case M_HALF:
				REFRAME(short);
				break;
			case M_INT:
			case M_UINT:
				REFRAME(int);
				break;
			case M_FLOAT:
				REFRAME(float);
				break;
			default:
				assert(0);
				break;
			}
		}
		else {
			assert(0);
		}
	}
	else {
		m_image_copy(dest, src);
	}
}

void m_image_rotate_left(struct m_image *dest, const struct m_image *src)
{
	#define ROTATE_L(T)\
	{\
		T *src_data = (T *)src->data;\
		T *dest_pixel = (T *)dest->data;\
		for (y = 0; y < width;  y++)\
		for (x = 0; x < height; x++) {\
			T *src_pixel = src_data + (x * width + (width - 1 - y)) * comp;\
			for (c = 0; c < comp; c++)\
				dest_pixel[c] = src_pixel[c];\
			dest_pixel += comp;\
		}\
	}\

	int width = src->width;
	int height = src->height;
	int comp = src->comp;
	int x, y, c;

	m_image_create(dest, src->type, height, width, comp);

	switch(src->type)
	{
	case M_BYTE:
	case M_UBYTE:
		ROTATE_L(char);
		break;
	case M_SHORT:
	case M_USHORT:
	case M_HALF:
		ROTATE_L(short);
		break;
	case M_INT:
	case M_UINT:
		ROTATE_L(int);
		break;
	case M_FLOAT:
		ROTATE_L(float);
		break;
	default:
		assert(0);
		break;
	}
}

void m_image_rotate_right(struct m_image *dest, const struct m_image *src)
{
	#define ROTATE_R(T)\
	{\
		T *src_data = (T *)src->data;\
		T *dest_pixel = (T *)dest->data;\
		for (y = 0; y < width;  y++)\
		for (x = 0; x < height; x++) {\
			T *src_pixel = src_data + ((height - 1 - x) * width + y) * comp;\
			for (c = 0; c < comp; c++)\
				dest_pixel[c] = src_pixel[c];\
			dest_pixel += comp;\
		}\
	}\

	int width = src->width;
	int height = src->height;
	int comp = src->comp;
	int x, y, c;

	m_image_create(dest, src->type, height, width, comp);

	switch(src->type)
	{
	case M_BYTE:
	case M_UBYTE:
		ROTATE_R(char);
		break;
	case M_SHORT:
	case M_USHORT:
	case M_HALF:
		ROTATE_R(short);
		break;
	case M_INT:
	case M_UINT:
		ROTATE_R(int);
		break;
	case M_FLOAT:
		ROTATE_R(float);
		break;
	default:
		assert(0);
		break;
	}
}

void m_image_rotate_180(struct m_image *dest, const struct m_image *src)
{
	#define ROTATE_180(T)\
	{\
		T *src_data = (T *)src->data;\
		T *dest_pixel = (T *)dest->data;\
		for (y = 0; y < height;  y++)\
		for (x = 0; x < width; x++) {\
			T *src_pixel = src_data + ((height - 1 - y) * width + (width - 1 - x)) * comp;\
			for (c = 0; c < comp; c++)\
				dest_pixel[c] = src_pixel[c];\
			dest_pixel += comp;\
		}\
	}\

	int width = src->width;
	int height = src->height;
	int comp = src->comp;
	int x, y, c;

	m_image_create(dest, src->type, width, height, comp);

	switch(src->type)
	{
	case M_BYTE:
	case M_UBYTE:
		ROTATE_180(char);
		break;
	case M_SHORT:
	case M_USHORT:
	case M_HALF:
		ROTATE_180(short);
		break;
	case M_INT:
	case M_UINT:
		ROTATE_180(int);
		break;
	case M_FLOAT:
		ROTATE_180(float);
		break;
	default:
		assert(0);
		break;
	}
}

void m_image_mirror_x(struct m_image *dest, const struct m_image *src)
{
	#define MIRROR_X(T)\
	{\
		T *src_data = (T *)src->data;\
		T *dest_pixel = (T *)dest->data;\
		for (y = 0; y < height;  y++)\
		for (x = 0; x < width; x++) {\
			T *src_pixel = src_data + (y * width + (width - 1 - x)) * comp;\
			for (c = 0; c < comp; c++)\
				dest_pixel[c] = src_pixel[c];\
			dest_pixel += comp;\
		}\
	}\

	int width = src->width;
	int height = src->height;
	int comp = src->comp;
	int x, y, c;

	m_image_create(dest, src->type, width, height, comp);

	switch(src->type)
	{
	case M_BYTE:
	case M_UBYTE:
		MIRROR_X(char);
		break;
	case M_SHORT:
	case M_USHORT:
	case M_HALF:
		MIRROR_X(short);
		break;
	case M_INT:
	case M_UINT:
		MIRROR_X(int);
		break;
	case M_FLOAT:
		MIRROR_X(float);
		break;
	default:
		assert(0);
		break;
	}
}

void m_image_mirror_y(struct m_image *dest, const struct m_image *src)
{
	#define MIRROR_Y(T)\
	{\
		T *src_data = (T *)src->data;\
		T *dest_pixel = (T *)dest->data;\
		for (y = 0; y < height;  y++)\
		for (x = 0; x < width; x++) {\
			T *src_pixel = src_data + ((height - 1 - y) * width + x) * comp;\
			for (c = 0; c < comp; c++)\
				dest_pixel[c] = src_pixel[c];\
			dest_pixel += comp;\
		}\
	}\

	int width = src->width;
	int height = src->height;
	int comp = src->comp;
	int x, y, c;

	m_image_create(dest, src->type, width, height, comp);

	switch(src->type)
	{
	case M_BYTE:
	case M_UBYTE:
		MIRROR_Y(char);
		break;
	case M_SHORT:
	case M_USHORT:
	case M_HALF:
		MIRROR_Y(short);
		break;
	case M_INT:
	case M_UINT:
		MIRROR_Y(int);
		break;
	case M_FLOAT:
		MIRROR_Y(float);
		break;
	default:
		assert(0);
		break;
	}
}

void m_image_sub_pixel(const struct m_image *src, float x, float y, float *result)
{
	float *colors0, *colors1, *colors2, *colors3;
	float *src_data = (float *)src->data;
	int width = src->width;
	int height = src->height;
	int comp = src->comp;
	int c;
	float fx, fy;
	int wm = width - 1;
	int hm = height - 1;
	int ix, iy, ix2, iy2;

	ix = (int)x;
	iy = (int)y;
	fx = x - (float)ix;
	fy = y - (float)iy;
	ix = M_CLAMP(ix, 0, wm);
	iy = M_CLAMP(iy, 0, hm);
	ix2 = ix + 1;
	iy2 = iy + 1;
	ix2 = M_MIN(ix2, wm);
	iy2 = M_MIN(iy2, hm);
	
	colors0 = src_data + (width * iy  + ix)  * comp;
	colors1 = src_data + (width * iy  + ix2) * comp;
	colors2 = src_data + (width * iy2 + ix)  * comp;
	colors3 = src_data + (width * iy2 + ix2) * comp;
	
	for(c = 0; c < comp; c++) {
		float A = colors0[c] + (colors2[c] - colors0[c]) * fy;
		float B = colors1[c] + (colors3[c] - colors1[c]) * fy;
		result[c] = A + (B - A) * fx;
	}
}
