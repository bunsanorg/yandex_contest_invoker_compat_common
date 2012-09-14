#define BOOST_TEST_MODULE compat
#include <boost/test/unit_test.hpp>

#include "yandex/contest/tests/BoostExecTest.hpp"

#include "yandex/contest/invoker/compat/Error.hpp"
#include "yandex/contest/invoker/compat/ContainerContext.hpp"

using namespace yandex::contest::invoker;

struct ContextFixture
{
    ContextFixture()
    {
        cnt = compat::ContainerContext::create();
        for (std::size_t i = 0; i < pgSize; ++i)
        {
            pg[i] = cnt->createProcessGroup();
            for (std::size_t j = 0; j < pSize; ++j)
                p[i][j] = pg[i].context().createProcess("true");
        }
    }

    void verify()
    {
        for (std::size_t i = 0; i < pgSize; ++i)
        {
            verifyPG(i);
        }
    }

    void verifyPG(const std::size_t i)
    {
        BOOST_TEST_CHECKPOINT("Verifying process group");
        pg[i].context();
        for (std::size_t j = 0; j < pSize; ++j)
            verifyP(i, j);
    }

    void verifyP(const std::size_t i, const std::size_t j)
    {
        BOOST_TEST_CHECKPOINT("Verifying process");
        p[i][j].context();
    }

    void verifyNo()
    {
        for (std::size_t i = 0; i < pgSize; ++i)
        {
            BOOST_CHECK_THROW(pg[i].context(), compat::Error);
            verifyNoPG(i);
        }
    }

    void verifyNoPG(const std::size_t i)
    {
        for (std::size_t j = 0; j < pSize; ++j)
            verifyNoP(i, j);
    }

    void verifyNoP(const std::size_t i, const std::size_t j)
    {
        BOOST_CHECK_THROW(p[i][j].context(), compat::Error);
    }

    static constexpr std::size_t pgSize = 2, pSize = 2;

    compat::ContainerContextPointer cnt;
    compat::ProcessGroupHandle pg[pgSize];
    compat::ProcessHandle p[pgSize][pSize];
};

BOOST_FIXTURE_TEST_SUITE(Context, ContextFixture)

BOOST_AUTO_TEST_CASE(Container__reset)
{
    cnt.reset();
    verifyNo();
}

BOOST_AUTO_TEST_CASE(ProcessGroupHandle__destroy)
{
    pg[0].destroy();
    verifyNoPG(0);
    for (std::size_t i = 1; i < pgSize; ++i)
        verifyPG(i);
}

BOOST_AUTO_TEST_CASE(ProcessHandle__destroy)
{
    p[0][0].destroy();
    verifyNoP(0, 0);
    for (std::size_t j = 1; j < pSize; ++j)
        verifyP(0, j);
    pg[0].context(); // should not throw
    for (std::size_t i = 1; i < pgSize; ++i)
        verifyPG(i);
}

BOOST_AUTO_TEST_SUITE_END()
