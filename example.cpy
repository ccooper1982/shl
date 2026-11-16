

fn test1()
{
    print_test(1);

    pipeline := proc("find", home()+"/projects/shl", "-type", "f", "-name", "*.cpp")
              | proc("wc", "-l");

    result := exec(pipeline);

    if (exit_status(result) == 0) {
        println("C++ files found: ", result);
    }
    else {
        println("Failed to count C++ files");
    }
}


fn test2()
{
    print_test(2);

    pipeline := proc("seq", 1, 100000)
             | proc("grep", 5)
             | proc("sort", "-r")
             | proc("wc", "-l");

    result := exec(pipeline);

    if (exit_status(result) == 0) {
        println("Count: ", result);
    }
    else {
        println("Exit status: ", exit_status(result));
    }
}


fn test3()
{
    print_test(3);

    pipeline := proc("printf", "hello world")
             | proc("grep", "banana");

    result := exec(pipeline);

    if (exit_status(result) == 0) {
        println("Output: [", result, "]");
    }
    else {
        println("Exit status: ", exit_status(result));
    }
}


fn test4()
{
    print_test(4);

    pipeline := proc("seq", "1", "100000")
             | proc("grep", "5")
             | proc("wc", "-l");

    result := exec(pipeline);

    println("Exit status: ", exit_status(result));
    println("Numbers containing 5: ", result);
}

fn test5()
{
    print_test(5);

    println(env_exists("ZABC"));
    env_set("ZABC", "hello");
    println(env("ZABC"));
    println(env_exists("ZABC"));
}

fn test6()
{
    print_test(6);

    dir := home()+"/projects/shl/tests/tmp";

    println(path_exists(dir));
    println(dir_create(dir));
    println(path_exists(dir));
    println(file_create(dir + "/a.txt"));

    println(dir_create("/etc/abc_noperms"));
    println("Code: ", error_code(), " Reason: ", error_message());

    println(dir_create("/tmp/shl_test_dir"));
    println(error_code());
}

fn print_test(n: int)
{
    println("-------");
    println("Test: " , n);
    println("-------");
}



test1();
test2();
test3();
test4();
test5();
test6();
