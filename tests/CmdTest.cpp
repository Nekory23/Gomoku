#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "Gomoku.hpp"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

class ClassTest : protected gomoku::Game
{
    public:
        ClassTest() = default;
        ~ClassTest() = default;

        void test_function(std::vector<std::string> cmd) noexcept { HandleCmd(cmd); };

        void setIsStarted(bool val) noexcept { _isStarted = val; };

        bool getHasEnded() const noexcept { return _hasEnded; };
};

Test(test_split, split)
{
    std::string str = "coucou toi";
    std::vector<std::string> res;
    std::vector<std::string> res_final;

    res_final.push_back("coucou");
    res_final.push_back("toi");

    res = Split(str, ' ');

    cr_assert_str_eq(res_final[0].c_str(), res[0].c_str());
    cr_assert_str_eq(res_final[1].c_str(), res[1].c_str());
}

Test(test_split2, split)
{
    std::string str = "coucou toi et toi";
    std::vector<std::string> res;
    std::vector<std::string> res_final;

    res_final.push_back("coucou");
    res_final.push_back("toi");
    res_final.push_back("et");
    res_final.push_back("toi");

    res = Split(str, ' ');

    cr_assert_str_eq(res_final[0].c_str(), res[0].c_str());
    cr_assert_str_eq(res_final[1].c_str(), res[1].c_str());
    cr_assert_str_eq(res_final[2].c_str(), res[2].c_str());
    cr_assert_str_eq(res_final[3].c_str(), res[3].c_str());
}

Test(cmd1, cmd, .init=redirect_all_stdout)
{
    ClassTest go;
    std::vector<std::string> cmd;

    cmd.push_back("test");
    go.test_function(cmd);
    cr_assert_stdout_eq_str("UNKNOWN command not found\n", "");
}

Test(cmd2, cmd, .init=redirect_all_stdout)
{
    ClassTest go;
    std::vector<std::string> cmd;

    cmd.push_back("END");
    go.test_function(cmd);
    cr_assert_stdout_eq_str("ERROR the game hasn't started yet\n", "");
}

Test(cmd3, cmd, .init=redirect_all_stdout)
{
    ClassTest go;
    std::vector<std::string> cmd;

    cmd.push_back("END");
    cmd.push_back("dsjijh");
    go.test_function(cmd);
    cr_assert_stdout_eq_str("ERROR command don't take argument\n", "");
}

Test(cmd4, cmd, .init=redirect_all_stdout)
{
    ClassTest go;
    std::vector<std::string> cmd;

    cmd.push_back("BEGIN");
    go.test_function(cmd);
    cr_assert_stdout_eq_str("ERROR no map specified\n", "");
}

Test(cmd5, cmd, .init=redirect_all_stdout)
{
    ClassTest go;
    std::vector<std::string> cmd;

    cmd.push_back("BEGIN");
    cmd.push_back("t-yfg");
    go.test_function(cmd);
    cr_assert_stdout_eq_str("ERROR this command doesn't take arguments\n", "");
}


Test(cmd6, cmd, .init=redirect_all_stdout)
{
    ClassTest go;
    std::vector<std::string> cmd;

    cmd.push_back("TURN");
    go.test_function(cmd);
    cr_assert_stdout_eq_str("ERROR this command takes a position '[x],[y]' as argument\n", "");
}

Test(cmd7, cmd, .init=redirect_all_stdout)
{
    ClassTest go;
    std::vector<std::string> cmd;

    cmd.push_back("TURN");
    cmd.push_back("0");
    go.test_function(cmd);
    cr_assert_stdout_eq_str("ERROR the game has not started yet\n", "");
}

Test(cmd8, cmd, .init=redirect_all_stdout)
{
    ClassTest go;
    std::vector<std::string> cmd;

    cmd.push_back("RESTART");
    cmd.push_back("0");
    go.test_function(cmd);
    cr_assert_stdout_eq_str("ERROR this command doesn't take arguments\n", "");
}

Test(cmd9, cmd, .init=redirect_all_stdout)
{
    ClassTest go;
    std::vector<std::string> cmd;

    cmd.push_back("RESTART");
    go.test_function(cmd);
    cr_assert_stdout_eq_str("ERROR cannot restart a game that hasn't started\n", "");
}

Test(cmd10, cmd, .init=redirect_all_stdout)
{
    ClassTest go;
    std::vector<std::string> cmd;

    cmd.push_back("START");
    cmd.push_back("0");
    go.test_function(cmd);
    cr_assert_stdout_eq_str("ERROR unsupported size\n", "");
}

Test(cmd11, cmd, .init=redirect_all_stdout)
{
    ClassTest go;
    std::vector<std::string> cmd;

    cmd.push_back("START");
    go.test_function(cmd);
    cr_assert_stdout_eq_str("ERROR invalid argument\n", "");
}

Test(functional, functional, .init=redirect_all_stdout)
{
    ClassTest go;
    std::vector<std::string> cmd;

    cmd.push_back("START");
    cmd.push_back("20");
    go.test_function(cmd);
    cr_assert_stdout_eq_str("OK - everything is good\n", "");
}

Test(functional2, functional, .init=redirect_all_stdout)
{
    ClassTest go;
    std::vector<std::string> cmd;

    go.setIsStarted(true);
    cmd.push_back("END");
    go.test_function(cmd);
    cr_assert_eq(true, go.getHasEnded());
}