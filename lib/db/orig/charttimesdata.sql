USE jody;

insert into ChartTimes (Name, HTFMinutes, HTF, ITF, STF) values ('Hourly', 'H3',  180,   'm30', 30,   'm5',  5);
insert into ChartTimes (Name, HTFMinutes, HTF, ITF, STF) values ('Half Day', 'H6',  360,   'H1',  60,   'm10', 10);
insert into ChartTimes (Name, HTFMinutes, HTF, ITF, STF) values ('Daily', 'D1',  1440,  'H3',  180,  'm30', 30);
insert into ChartTimes (Name, HTFMinutes, HTF, ITF, STF) values ('Half Week', 'H36', 2160,  'H6',  360,  'H1',  60);
insert into ChartTimes (Name, HTFMinutes, HTF, ITF, STF) values ('Weekly', 'W1',  10080, 'D1',  1440, 'H4',  240);
