#define BOOST_TEST_MODULE libitppTest
#include <boost/test/unit_test.hpp>

#include "testconfig.h"

#include <boost/filesystem.hpp>
namespace bf = boost::filesystem;

#include <itpp/itbase.h>
#include <iostream>

#define P(X) std::cout << #X << ":\n" << X << std::endl;

/// Test operations on matrices.
BOOST_AUTO_TEST_CASE(matrix_test) {
    itpp::mat A = "1 2 3; 4 5 6; 7 8 9";
    P(A);
    itpp::mat B = "1; 2; 3";
    P(B);

    // matrix product
    itpp::mat C = A*B;
    P(C);

    // hermitian transposition
    itpp::mat D = B.hermitian_transpose() * A;
    P(D)
}

/// Test operations on vectors.
BOOST_AUTO_TEST_CASE(vector_test) {
    itpp::vec v = itpp::linspace(0, 10, 10+1);
    P(v);
    itpp::vec u = itpp::linspace(1, 10, 10);
    P(u);

    std::string us = itpp::to_str(u);
    P(us);
}

namespace test {

/// ITPP file test fixture.
struct FileFixture {
    FileFixture() : filePath(bf::temp_directory_path() / bf::path("itpp_test.it")) {}
    ~FileFixture() { bf::remove_all(filePath); }
    bf::path filePath;
};

}

/// Test write/reat to itpp file.
BOOST_FIXTURE_TEST_CASE(itpp_file, test::FileFixture) {
    using namespace itpp;

    /* write to file */
    int i = -22;
    double d = 3.1415;
    vec v = "1 2 3 4 5";
    mat m = "1 2 3; 1 2 3";
    {
        it_file file(filePath.string());
        file << Name("i") << i;
        file << Name("d") << d;
        file << Name("v") << v;
        file << Name("m") << m;
        file.close();
    }

    /* read from file */
    int ii;
    double dd;
    vec vv;
    mat mm;
    {
        it_file file(filePath.string());
        file >> Name("i") >> ii;
        file >> Name("d") >> dd;
        file >> Name("v") >> vv;
        file >> Name("m") >> mm;
        file.close();
    }
    BOOST_CHECK_EQUAL(i, ii);
    BOOST_CHECK_EQUAL(d, dd);
    BOOST_CHECK_EQUAL(v, vv);
    BOOST_CHECK_EQUAL(m, mm);
}

/// Test read from itpp file generated from matlab.
BOOST_AUTO_TEST_CASE(matlab_file) {
    using namespace itpp;

    const std::string filename = TEST_DATA_DIR "/matlab_test.it";
    P(filename);

    vec sig;
    ivec sil;
    mat wts;

    it_ifile file(filename);

    file >> Name("featuresSignal") >> sig;
    P(sig);
    file >> Name("featuresSilence") >> sil;
    P(sil);
    file >> Name("wts") >> wts;
    P(wts);
}

