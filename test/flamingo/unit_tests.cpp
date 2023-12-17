#include "unit_tests.h"

#include <QDebug>

TEST(DrawerTest, BorderTest) {
    drawer dr;
    std::vector<QVector3D> points = {
        QVector3D(0, 0, 0),
        QVector3D(2, 1, 0),
        QVector3D(3, 5, 0),
        QVector3D(6, 4, 0)
    };



    std::tuple<int, int, int, int> result = dr.border(points);

    EXPECT_EQ(std::get<0>(result), 5); // ymax
    EXPECT_EQ(std::get<1>(result), 0); // ymin
    EXPECT_EQ(std::get<2>(result), 6); // xmax
    EXPECT_EQ(std::get<3>(result), 0); // xmin
}

TEST(DrawerTest, BorderTest2) {
    drawer dr = drawer(100, 100);
    std::vector<QVector3D> points = {
        QVector3D(-23, 0, 13),
        QVector3D(2, 102, 43),
        QVector3D(3, 5, 0),
        QVector3D(6, 4, 0)
    };



    std::tuple<int, int, int, int> result = dr.border(points);

    EXPECT_EQ(std::get<0>(result), 99); // ymax
    EXPECT_EQ(std::get<1>(result), 0); // ymin
    EXPECT_EQ(std::get<2>(result), 6); // xmax
    EXPECT_EQ(std::get<3>(result), 0); // xmin
}

TEST(planeCoefTest, planeCoefTest) {
    drawer dr;
    std::vector<QVector3D> points = {
        QVector3D(0, 0, 3),
        QVector3D(2, 1, 3),
        QVector3D(1, 2, 3)
    };

    std::tuple<int, int, int, int> result = dr.plane_coef(points);

    EXPECT_EQ(std::get<0>(result), 0);   // a
    EXPECT_EQ(std::get<1>(result), 0); // b
    EXPECT_EQ(std::get<2>(result), 3);   // c
    EXPECT_EQ(std::get<3>(result), -9); // d
}

TEST(planeCoefTest, planeCoefTest1) {
    drawer dr;
    std::vector<QVector3D> points = {
        QVector3D(4, 0, 0),
        QVector3D(67, 1, 9),
        QVector3D(2, 8, 3)
    };

    std::tuple<int, int, int, int> result = dr.plane_coef(points);

    EXPECT_EQ(std::get<0>(result), -69);   // a
    EXPECT_EQ(std::get<1>(result), -207); // b
    EXPECT_EQ(std::get<2>(result), 506);   // c
    EXPECT_EQ(std::get<3>(result), 276); // d
}

TEST(DrawerTest, PutShadowPolygonTest) {
    drawer dr;
    std::vector<std::vector<double>> zb(100, std::vector<double>(100, INT_MIN));
    std::vector<QVector3D> points = {
        QVector3D(0, 0, 0),
        QVector3D(2, 1, 0),
        QVector3D(3, 5, 0)
    };
    light ls(QVector3D(0, 0, 5), 0.5);

    dr.putShadowPolygon(zb, points, ls);

    EXPECT_EQ(zb[-1][0], std::numeric_limits<double>::max());
    EXPECT_EQ(zb[2][1], (QVector3D(2, 1, 0) - ls.get_pos()).length());
    EXPECT_EQ(zb[4][5], std::numeric_limits<double>::max());
}

TEST(DrawerTest, PutShadowBufferTest) {
    drawer dr;
    std::vector<std::vector<double>> zb(100, std::vector<double>(100, std::numeric_limits<double>::max()));
    std::vector<object> objects;
    objects.emplace_back();
    polygon p(QVector3D(0, 0, 0), QVector3D(2, 1, 0), QVector3D(3, 5, 0));
    std::vector<polygon> polys;
    polys.push_back(p);
    objects.push_back(polys);
    light ls(QVector3D(0, 0, 5), 0.5);

    dr.putShadowBuffer(zb, objects, ls);

    EXPECT_EQ(zb[0][0], std::numeric_limits<double>::max());
    EXPECT_EQ(zb[2][1], (QVector3D(2, 1, 0) - ls.get_pos()).length());
    EXPECT_EQ(zb[3][5], std::numeric_limits<double>::max());
}

TEST(isInsideTest, isInsideTest) {
    drawer dr;
    std::vector<QVector3D> points = {
        QVector3D(0, 0, 0),
        QVector3D(2, 1, 0),
        QVector3D(3, 5, 0)
    };
    int x = 1;
    int y = 2;

    bool result = dr.is_inside(x, y, points);

    EXPECT_TRUE(result);
}

TEST(isInsideTest, isInsideTest1) {
    drawer dr;
    std::vector<QVector3D> points = {
        QVector3D(0, 0, 0),
        QVector3D(2, 1, 0),
        QVector3D(3, 5, 0)
    };
    int x = -1;
    int y = 2;

    bool result = dr.is_inside(x, y, points);

    EXPECT_FALSE(result);
}

TEST(isInsideTest, isInsideTest2) {
    drawer dr;
    std::vector<QVector3D> points = {
        QVector3D(0, 0, 0),
        QVector3D(2, 1, 0),
        QVector3D(3, 5, 0)
    };
    int x = 3;
    int y = 5;

    bool result = dr.is_inside(x, y, points);

    EXPECT_TRUE(result);
}

int unit_tests(int argc, char *argv[])
{
    std::cout << "GOOGLE TESTS:" << std::endl;

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
