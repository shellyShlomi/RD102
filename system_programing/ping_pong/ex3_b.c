/*

    if (child_pid == -1)
    {
        exit(EXIT_FAILURE);
    }
    else if (child_pid > 0)
    {
        flag = 1;
        while (0 == status && flag)
        {
            printf("PING\n");

            status = kill(child_pid, SIGUSR1);
        }
    }
    else
    {
        execl("/home/shelly/git/system_programing/ping_pong/ex2_child", "shelly");
    } */