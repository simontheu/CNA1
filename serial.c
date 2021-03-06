#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

int
set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                error("error from tcgetattr");
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 1;            // read doesn't block
        tty.c_cc[VTIME] = 2;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                error("error from tcsetattr");
                return -1;
        }
        return 0;
}

void
set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                error ("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 0;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                error("error setting term attributes");
}

int set_up_port(char * portname)
{

    int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0)
    {
        error ("error %d opening %s: %s", errno);//o, portname, strerror (errno));
        return;
    }

    set_interface_attribs (fd, B9600, 0);  // set speed to 9,600 bps, 8n1 (no parity)
    set_blocking (fd, 0);                // set no blocking

    write (fd, "SVF 8\n", 6);           // set video format to 1080i 50
    usleep ((6 + 25) * 10);             // sleep enough to transmit the 7 plus

    write (fd, "SI 0\n", 5);           // set iris to be auto
    usleep ((5 + 25) * 10);             // sleep enough to transmit the 7 plus
    
    write (fd, "SAL 100\n", 8);           // set auto level to max
    usleep ((8 + 25) * 10);             // sleep enough to transmit the 7 plus

    write (fd, "SAS 100\n", 8);           // set auto level speed to be max
    usleep ((8 + 25) * 10);             // sleep enough to transmit the 7 plus
    
    write (fd, "SGM 0\n", 6);           // set gain to be manual
    usleep ((6 + 25) * 10);             // sleep enough to transmit the 7 plus

    write (fd, "SGV 0\n", 6);           // set gain value to be 0
    usleep ((6 + 25) * 10);             // sleep enough to transmit the 7 plus
    
    write (fd, "SSM 0\n", 6);           // set shutter mode to be manual
    usleep ((6 + 25) * 10);             // sleep enough to transmit the 7 plus

    write (fd, "SSV 0\n", 6);           // set shutter amount to open
    usleep ((6 + 25) * 10);             // sleep enough to transmit the 7 plus
    
    write (fd, "SSM 0\n", 6);           // set shutter mode to be manual
    usleep ((6 + 25) * 10);             // sleep enough to transmit the 7 plus
    
    write (fd, "SWM 11\n", 7);           // set white balance mode to be manual
    usleep ((7 + 25) * 10);             // sleep enough to transmit the 7 plus
    
    write (fd, "SAG 0\n", 6);           // set auto gamma to off
    usleep ((6 + 25) * 10);             // sleep enough to transmit the 7 plus
    
    
    usleep(100);
    char buf [100];

    int n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read
    printf(buf);

    return fd;
}
