#include <check.h>

#include "../core/parser.h"
#include "../core/s21_3dviewer.h"
#include "../core/transformations.h"

#define EPS 1e-06

// PARSER

START_TEST(parser_nofile) {
  data d = {0, 0, NULL, NULL};
  char filename[] = "nofile.obj";
  int res = parse_file(filename, &d);
  ck_assert_uint_eq(res, ERROR);
}
END_TEST

START_TEST(parser_null) {
  data d = {0, 0, NULL, NULL};
  char *filename = NULL;
  int res = parse_file(filename, &d);
  ck_assert_uint_eq(res, ERROR);
}
END_TEST

// X AXIS ROTATION

START_TEST(x_rotation_1) {
  data d = {0, 0, NULL, NULL};
  char filename[] = "tests/cube.obj";
  double vertices[] = {1.000000,  0.597672,  -1.281713, 1.000000,  -1.281713,
                       -0.597672, 1.000000,  1.281713,  0.597672,  1.000000,
                       -0.597672, 1.281713,  -1.000000, 0.597672,  -1.281713,
                       -1.000000, -1.281713, -0.597672, -1.000000, 1.281713,
                       0.597672,  -1.000000, -0.597672, 1.281713};
  parse_file(filename, &d);
  x_rotation(&d, 20);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(x_rotation_2) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {1.000000,  1.281713,  -0.597672, 1.000000,  -0.597672,
                       -1.281713, 1.000000,  0.597672,  1.281713,  1.000000,
                       -1.281713, 0.597672,  -1.000000, 1.281713,  -0.597672,
                       -1.000000, -0.597672, -1.281713, -1.000000, 0.597672,
                       1.281713,  -1.000000, -1.281713, 0.597672};
  parse_file(filename, &d);
  x_rotation(&d, -20);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(x_rotation_3) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {1.000000,  -0.366025, -1.366025, 1.000000,  -1.366025,
                       0.366025,  1.000000,  1.366025,  -0.366025, 1.000000,
                       0.366025,  1.366025,  -1.000000, -0.366025, -1.366025,
                       -1.000000, -1.366025, 0.366025,  -1.000000, 1.366025,
                       -0.366025, -1.000000, 0.366025,  1.366025};
  parse_file(filename, &d);
  x_rotation(&d, 1500);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

// Y AXIS ROTATION

START_TEST(y_rotation_1) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {0.597672,  1.000000,  -1.281713, 0.597672,  -1.000000,
                       -1.281713, 1.281713,  1.000000,  0.597672,  1.281713,
                       -1.000000, 0.597672,  -1.281713, 1.000000,  -0.597672,
                       -1.281713, -1.000000, -0.597672, -0.597672, 1.000000,
                       1.281713,  -0.597672, -1.000000, 1.281713};
  parse_file(filename, &d);
  y_rotation(&d, 20);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(y_rotation_2) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {1.281713,  1.000000,  -0.597672, 1.281713,  -1.000000,
                       -0.597672, 0.597672,  1.000000,  1.281713,  0.597672,
                       -1.000000, 1.281713,  -0.597672, 1.000000,  -1.281713,
                       -0.597672, -1.000000, -1.281713, -1.281713, 1.000000,
                       0.597672,  -1.281713, -1.000000, 0.597672};
  parse_file(filename, &d);
  y_rotation(&d, -20);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(y_rotation_3) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {-0.366025, 1.000000,  -1.366025, -0.366025, -1.000000,
                       -1.366025, 1.366025,  1.000000,  -0.366025, 1.366025,
                       -1.000000, -0.366025, -1.366025, 1.000000,  0.366025,
                       -1.366025, -1.000000, 0.366025,  0.366025,  1.000000,
                       1.366025,  0.366025,  -1.000000, 1.366025};
  parse_file(filename, &d);
  y_rotation(&d, 1500);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

// Z AXIS ROTATION

START_TEST(z_rotation_1) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {1.281713,  0.597672,  -1.000000, 0.597672,  -1.281713,
                       -1.000000, 1.281713,  0.597672,  1.000000,  0.597672,
                       -1.281713, 1.000000,  -0.597672, 1.281713,  -1.000000,
                       -1.281713, -0.597672, -1.000000, -0.597672, 1.281713,
                       1.000000,  -1.281713, -0.597672, 1.000000};
  parse_file(filename, &d);
  z_rotation(&d, 20);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(z_rotation_2) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {0.597672,  1.281713,  -1.000000, 1.281713,  -0.597672,
                       -1.000000, 0.597672,  1.281713,  1.000000,  1.281713,
                       -0.597672, 1.000000,  -1.281713, 0.597672,  -1.000000,
                       -0.597672, -1.281713, -1.000000, -1.281713, 0.597672,
                       1.000000,  -0.597672, -1.281713, 1.000000};
  parse_file(filename, &d);
  z_rotation(&d, -20);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(z_rotation_3) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {1.366025,  -0.366025, -1.000000, -0.366025, -1.366025,
                       -1.000000, 1.366025,  -0.366025, 1.000000,  -0.366025,
                       -1.366025, 1.000000,  0.366025,  1.366025,  -1.000000,
                       -1.366025, 0.366025,  -1.000000, 0.366025,  1.366025,
                       1.000000,  -1.366025, 0.366025,  1.000000};
  parse_file(filename, &d);
  z_rotation(&d, 1500);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(scale_1) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {5.000000,  5.000000,  -5.000000, 5.000000,  -5.000000,
                       -5.000000, 5.000000,  5.000000,  5.000000,  5.000000,
                       -5.000000, 5.000000,  -5.000000, 5.000000,  -5.000000,
                       -5.000000, -5.000000, -5.000000, -5.000000, 5.000000,
                       5.000000,  -5.000000, -5.000000, 5.000000};
  parse_file(filename, &d);
  scale_t(&d, 5);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(scale_2) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {0.500000,  0.500000,  -0.500000, 0.500000,  -0.500000,
                       -0.500000, 0.500000,  0.500000,  0.500000,  0.500000,
                       -0.500000, 0.500000,  -0.500000, 0.500000,  -0.500000,
                       -0.500000, -0.500000, -0.500000, -0.500000, 0.500000,
                       0.500000,  -0.500000, -0.500000, 0.500000};
  parse_file(filename, &d);
  scale_t(&d, 0.5);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(scale_3) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {1000.000000,  1000.000000,  -1000.000000, 1000.000000,
                       -1000.000000, -1000.000000, 1000.000000,  1000.000000,
                       1000.000000,  1000.000000,  -1000.000000, 1000.000000,
                       -1000.000000, 1000.000000,  -1000.000000, -1000.000000,
                       -1000.000000, -1000.000000, -1000.000000, 1000.000000,
                       1000.000000,  -1000.000000, -1000.000000, 1000.000000};
  parse_file(filename, &d);
  scale_t(&d, 1000);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

// X MOVE

START_TEST(x_move_1) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {9.000000,  1.000000,  -1.000000, 9.000000, -1.000000,
                       -1.000000, 9.000000,  1.000000,  1.000000, 9.000000,
                       -1.000000, 1.000000,  7.000000,  1.000000, -1.000000,
                       7.000000,  -1.000000, -1.000000, 7.000000, 1.000000,
                       1.000000,  7.000000,  -1.000000, 1.000000};
  parse_file(filename, &d);
  x_move(&d, 8);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(x_move_2) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {-3.000000, 1.000000,  -1.000000, -3.000000, -1.000000,
                       -1.000000, -3.000000, 1.000000,  1.000000,  -3.000000,
                       -1.000000, 1.000000,  -5.000000, 1.000000,  -1.000000,
                       -5.000000, -1.000000, -1.000000, -5.000000, 1.000000,
                       1.000000,  -5.000000, -1.000000, 1.000000};
  parse_file(filename, &d);
  x_move(&d, -4);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(x_move_3) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {0.700000,  1.000000,  -1.000000, 0.700000,  -1.000000,
                       -1.000000, 0.700000,  1.000000,  1.000000,  0.700000,
                       -1.000000, 1.000000,  -1.300000, 1.000000,  -1.000000,
                       -1.300000, -1.000000, -1.000000, -1.300000, 1.000000,
                       1.000000,  -1.300000, -1.000000, 1.000000};
  parse_file(filename, &d);
  x_move(&d, -0.3);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

// Y MOVE

START_TEST(y_move_1) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {1.000000,  7.000000,  -1.000000, 1.000000,  5.000000,
                       -1.000000, 1.000000,  7.000000,  1.000000,  1.000000,
                       5.000000,  1.000000,  -1.000000, 7.000000,  -1.000000,
                       -1.000000, 5.000000,  -1.000000, -1.000000, 7.000000,
                       1.000000,  -1.000000, 5.000000,  1.000000};
  parse_file(filename, &d);
  y_move(&d, 6);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(y_move_2) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {1.000000,  -1.000000, -1.000000, 1.000000,  -3.000000,
                       -1.000000, 1.000000,  -1.000000, 1.000000,  1.000000,
                       -3.000000, 1.000000,  -1.000000, -1.000000, -1.000000,
                       -1.000000, -3.000000, -1.000000, -1.000000, -1.000000,
                       1.000000,  -1.000000, -3.000000, 1.000000};
  parse_file(filename, &d);
  y_move(&d, -2);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(y_move_3) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {1.000000,  -7.900000, -1.000000, 1.000000,  -9.900000,
                       -1.000000, 1.000000,  -7.900000, 1.000000,  1.000000,
                       -9.900000, 1.000000,  -1.000000, -7.900000, -1.000000,
                       -1.000000, -9.900000, -1.000000, -1.000000, -7.900000,
                       1.000000,  -1.000000, -9.900000, 1.000000};
  parse_file(filename, &d);
  y_move(&d, -8.9);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

// Z MOVE

START_TEST(z_move_1) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {1.000000,  1.000000,  1.500000,  1.000000,  -1.000000,
                       1.500000,  1.000000,  1.000000,  3.500000,  1.000000,
                       -1.000000, 3.500000,  -1.000000, 1.000000,  1.500000,
                       -1.000000, -1.000000, 1.500000,  -1.000000, 1.000000,
                       3.500000,  -1.000000, -1.000000, 3.500000};
  parse_file(filename, &d);
  z_move(&d, 2.5);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(z_move_2) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {1.000000,  1.000000,  -5.000000, 1.000000,  -1.000000,
                       -5.000000, 1.000000,  1.000000,  -3.000000, 1.000000,
                       -1.000000, -3.000000, -1.000000, 1.000000,  -5.000000,
                       -1.000000, -1.000000, -5.000000, -1.000000, 1.000000,
                       -3.000000, -1.000000, -1.000000, -3.000000};
  parse_file(filename, &d);
  z_move(&d, -4);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

START_TEST(z_move_3) {
  data d = {0, 0, NULL, NULL};
  char *filename = "tests/cube.obj";
  double vertices[] = {1.000000,   1.000000,  -11.000000, 1.000000,  -1.000000,
                       -11.000000, 1.000000,  1.000000,   -9.000000, 1.000000,
                       -1.000000,  -9.000000, -1.000000,  1.000000,  -11.000000,
                       -1.000000,  -1.000000, -11.000000, -1.000000, 1.000000,
                       -9.000000,  -1.000000, -1.000000,  -9.000000};
  parse_file(filename, &d);
  z_move(&d, -10);
  ck_assert_uint_eq(d.count_index, 36);
  ck_assert_uint_eq(d.count_vertices, 8);

  for (size_t i = 0; i < d.count_vertices * 3; i++) {
    ck_assert_double_eq_tol(d.vertices[i], vertices[i], EPS);
  }

  clear_data(&d);
}
END_TEST

// SUITE

Suite *suite_3d(void) {
  Suite *s;
  s = suite_create("Check");

  // PARSER

  TCase *tc_parser_nofile;
  tc_parser_nofile = tcase_create("parser_nofile");
  suite_add_tcase(s, tc_parser_nofile);
  tcase_add_test(tc_parser_nofile, parser_nofile);

  TCase *tc_parser_null;
  tc_parser_null = tcase_create("parser_null");
  suite_add_tcase(s, tc_parser_null);
  tcase_add_test(tc_parser_null, parser_null);

  // X AXIS ROTATION

  TCase *tc_x_rotation_1;
  tc_x_rotation_1 = tcase_create("x_rotation_1");
  suite_add_tcase(s, tc_x_rotation_1);
  tcase_add_test(tc_x_rotation_1, x_rotation_1);

  TCase *tc_x_rotation_2;
  tc_x_rotation_2 = tcase_create("x_rotation_2");
  suite_add_tcase(s, tc_x_rotation_2);
  tcase_add_test(tc_x_rotation_2, x_rotation_2);

  TCase *tc_x_rotation_3;
  tc_x_rotation_3 = tcase_create("x_rotation_3");
  suite_add_tcase(s, tc_x_rotation_3);
  tcase_add_test(tc_x_rotation_3, x_rotation_3);

  // Y AXIS ROTATION

  TCase *tc_y_rotation_1;
  tc_y_rotation_1 = tcase_create("y_rotation_1");
  suite_add_tcase(s, tc_y_rotation_1);
  tcase_add_test(tc_y_rotation_1, y_rotation_1);

  TCase *tc_y_rotation_2;
  tc_y_rotation_2 = tcase_create("y_rotation_2");
  suite_add_tcase(s, tc_y_rotation_2);
  tcase_add_test(tc_y_rotation_2, y_rotation_2);

  TCase *tc_y_rotation_3;
  tc_y_rotation_3 = tcase_create("y_rotation_3");
  suite_add_tcase(s, tc_y_rotation_3);
  tcase_add_test(tc_y_rotation_3, y_rotation_3);

  // Z AXIS ROTATION

  TCase *tc_z_rotation_1;
  tc_z_rotation_1 = tcase_create("z_rotation_1");
  suite_add_tcase(s, tc_z_rotation_1);
  tcase_add_test(tc_z_rotation_1, z_rotation_1);

  TCase *tc_z_rotation_2;
  tc_z_rotation_2 = tcase_create("z_rotation_2");
  suite_add_tcase(s, tc_z_rotation_2);
  tcase_add_test(tc_z_rotation_2, z_rotation_2);

  TCase *tc_z_rotation_3;
  tc_z_rotation_3 = tcase_create("z_rotation_3");
  suite_add_tcase(s, tc_z_rotation_3);
  tcase_add_test(tc_z_rotation_3, z_rotation_3);

  // SCALE

  TCase *tc_scale_1;
  tc_scale_1 = tcase_create("scale_1");
  suite_add_tcase(s, tc_scale_1);
  tcase_add_test(tc_scale_1, scale_1);

  TCase *tc_scale_2;
  tc_scale_2 = tcase_create("scale_2");
  suite_add_tcase(s, tc_scale_2);
  tcase_add_test(tc_scale_2, scale_2);

  TCase *tc_scale_3;
  tc_scale_3 = tcase_create("scale_3");
  suite_add_tcase(s, tc_scale_3);
  tcase_add_test(tc_scale_3, scale_3);

  // X MOVE

  TCase *tc_x_move_1;
  tc_x_move_1 = tcase_create("x_move_1");
  suite_add_tcase(s, tc_x_move_1);
  tcase_add_test(tc_x_move_1, x_move_1);

  TCase *tc_x_move_2;
  tc_x_move_2 = tcase_create("x_move_2");
  suite_add_tcase(s, tc_x_move_2);
  tcase_add_test(tc_x_move_2, x_move_2);

  TCase *tc_x_move_3;
  tc_x_move_3 = tcase_create("x_move_3");
  suite_add_tcase(s, tc_x_move_3);
  tcase_add_test(tc_x_move_3, x_move_3);

  // Y MOVE

  TCase *tc_y_move_1;
  tc_y_move_1 = tcase_create("y_move_1");
  suite_add_tcase(s, tc_y_move_1);
  tcase_add_test(tc_y_move_1, y_move_1);

  TCase *tc_y_move_2;
  tc_y_move_2 = tcase_create("y_move_2");
  suite_add_tcase(s, tc_y_move_2);
  tcase_add_test(tc_y_move_2, y_move_2);

  TCase *tc_y_move_3;
  tc_y_move_3 = tcase_create("y_move_3");
  suite_add_tcase(s, tc_y_move_3);
  tcase_add_test(tc_y_move_3, y_move_3);

  // Z MOVE

  TCase *tc_z_move_1;
  tc_z_move_1 = tcase_create("z_move_1");
  suite_add_tcase(s, tc_z_move_1);
  tcase_add_test(tc_z_move_1, z_move_1);

  TCase *tc_z_move_2;
  tc_z_move_2 = tcase_create("z_move_2");
  suite_add_tcase(s, tc_z_move_2);
  tcase_add_test(tc_z_move_2, z_move_2);

  TCase *tc_z_move_3;
  tc_z_move_3 = tcase_create("z_move_3");
  suite_add_tcase(s, tc_z_move_3);
  tcase_add_test(tc_z_move_3, z_move_3);

  return s;
}

int main(void) {
  Suite *s = suite_3d();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  int nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
