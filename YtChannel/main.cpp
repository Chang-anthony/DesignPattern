/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <Channel.hpp>
#include <ChannelSubscriber.hpp>
#include <Waterball.hpp>
#include <Fireball.hpp>
#include <Video.hpp>
#include <utils.hpp>


int main()
{
    Channel* PewDiePie = new Channel("PewDiePie");
    Channel* waterball_school = new Channel("水球軟體學院");

    Waterball* waterball = new Waterball();
    Fireball* fireball = new Fireball();

    waterball->subscribe(waterball_school);
    waterball->subscribe(PewDiePie);
    fireball->subscribe(waterball_school);
    fireball->subscribe(PewDiePie);

    Video* video1 = new Video("C1M1S2", "這個世界正是物件導向的呢！", 240);
    waterball_school->upload(video1);

    Video* video2 = new Video("Hello guys", "Clickbait", 30);
    PewDiePie->upload(video2);

    Video* video3 = new Video("C1M1S3", "物件 vs. 類別", 60);
    waterball_school->upload(video3);

    Video* video4 = new Video("Minecraft", "Let’s play Minecraft", 1800);
    PewDiePie->upload(video4);

    return 0;
}