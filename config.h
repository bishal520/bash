/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int refresh_rate    = 60;     /* matches dwm's mouse event processing to your monitor's refresh rate for smoother window interactions */
static const unsigned int enable_noborder = 1;      /* toggles noborder feature (0=disabled, 1=enabled) */
static const unsigned int borderpx        = 1;      /* border pixel of windows */
static const unsigned int snap            = 26;     /* snap pixel */
static const int swallowfloating          = 1;      /* 1 means swallow floating windows by default */
static const unsigned int systraypinning  = 0;      /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft   = 0;      /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing  = 5;      /* systray spacing */
static const int systraypinningfailfirst  = 1;      /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray              = 1;      /* 0 means no systray */
static const int showbar                  = 1;      /* 0 means no bar */
static const int topbar                   = 1;      /* 0 means bottom bar */
#define ICONSIZE                            14      /* icon size */
#define ICONSPACING                         5       /* space between icon and title */
#define SHOWWINICON                         1       /* 0 means no winicon */
static const char *fonts[] = { "MesloLGS Nerd Font Mono:size=10", "NotoColorEmoji:pixelsize=16:antialias=true:autohint=true", "Font Awesome 6 Free Solid:size=12" };

static const char normbordercolor[]       = "#3B4252";
static const char normbgcolor[]           = "#2E3440";
static const char normfgcolor[]           = "#D8DEE9";
static const char selbordercolor[]        = "#434C5E";
static const char selbgcolor[]            = "#434C5E";
static const char selfgcolor[]            = "#ECEFF4";

static const char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel] =  { selfgcolor,  selbgcolor,  selbordercolor },
};

static const char *const autostart[] = {
  "xset", "s", "off", NULL,
  "xset", "s", "noblank", NULL,
  "xset", "-dpms", NULL,
  "dbus-update-activation-environment", "--systemd", "--all", NULL,
  "/usr/lib/mate-polkit/polkit-mate-authentication-agent-1", NULL,
  "flameshot", NULL,
  "dunst", NULL,
  "picom", "--animations", "-b", NULL,
  "sh", "-c", "feh --randomize --bg-fill /home/bishal/Pictures/backgrounds/*", NULL,
  "synergy", NULL,
  "slstatus", NULL,
  NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };


static const char ptagf[] = "[%s %s]";  /* format of a tag label */
static const char etagf[] = "[%s]";     /* format of an empty tag */
static const int lcaselbl = 0;          /* 1 means make tag label lowercase */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "kitty",   NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.75; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    { "\ue00d", tile },    /* Icon for tile layout */
    { "\uf009", NULL },    /* Icon for floating layout (replace with appropriate icon) */
    { "\uf2dc", monocle }, /* Icon for monocle layout (replace with appropriate icon) */
};


/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define STATUSBAR "dwmblocks"
/* commands */
static const char *launchercmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "kitty", NULL };

static Key keys[] = {
    /* modifier                     key            function                argument */
    { MODKEY,                       XK_r,          spawn,                  {.v = launchercmd} }, // launch applications
    { MODKEY|ControlMask,           XK_r,          spawn,                  SHCMD ("protonrestart")}, // restart protonvpn
    { MODKEY,                       XK_x,          spawn,                  {.v = termcmd } }, // open a terminal
    { MODKEY,                       XK_b,          spawn,                  SHCMD ("xdg-open https://")}, // open default browser
    { MODKEY,                       XK_p,          spawn,                  SHCMD ("flameshot full -p /media/drive/Screenshots/")}, // take a full-screen screenshot
    { MODKEY|ShiftMask,             XK_p,          spawn,                  SHCMD ("flameshot gui -p /media/drive/Screenshots/")}, // open flameshot GUI for screenshot selection
    { MODKEY|ControlMask,           XK_p,          spawn,                  SHCMD ("flameshot gui --clipboard")}, // copy screenshot to clipboard
    { MODKEY,                       XK_e,          spawn,                  SHCMD ("thunar")}, // open file manager
    { MODKEY|ShiftMask,             XK_w,          spawn,                  SHCMD ("feh --randomize --bg-fill /home/bishal/Pictures/backgrounds/*")},
    { MODKEY,                       XK_v,          spawn,                  SHCMD("amixer sset Master toggle") },
    { MODKEY|ShiftMask,             XK_b,          togglebar,              {0} }, // toggle bar visibility
    { MODKEY,                       XK_j,          focusstack,             {.i = +1 } }, // focus next window
    { MODKEY,                       XK_k,          focusstack,             {.i = -1 } }, // focus previous window
    { MODKEY|ShiftMask,             XK_j,          movestack,              {.i = +1 } }, // move window up in stack
    { MODKEY|ShiftMask,             XK_k,          movestack,              {.i = -1 } }, // move window down in stack
    { MODKEY,                       XK_i,          incnmaster,             {.i = +1 } }, // increase clients in master area
    { MODKEY,                       XK_d,          incnmaster,             {.i = -1 } }, // decrease clients in master area
    { MODKEY,                       XK_h,          setmfact,               {.f = -0.05} }, // decrease master area size
    { MODKEY,                       XK_l,          setmfact,               {.f = +0.05} }, // increase master area size
    { MODKEY|ShiftMask,             XK_h,          setcfact,               {.f = +0.25} }, // increase client size
    { MODKEY|ShiftMask,             XK_l,          setcfact,               {.f = -0.25} }, // decrease client size
    { MODKEY|ShiftMask,             XK_o,          setcfact,               {.f =  0.00} }, // reset client area
    { MODKEY,                       XK_Return,     zoom,                   {0} }, // move window to/from master area
    { MODKEY,                       XK_Tab,        view,                   {0} }, // view last focused tag
    { MODKEY,                       XK_q,          killclient,             {0} }, // close focused window
    { MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} }, // set tile layout
    { MODKEY,                       XK_f,          setlayout,              {.v = &layouts[1]} }, // set floating layout
    { MODKEY,                       XK_m,          fullscreen,             {0} }, // toggle fullscreen
    { MODKEY,                       XK_space,      setlayout,              {0} }, // toggle between current and previous layout
    { MODKEY|ShiftMask,             XK_m,          togglefloating,         {0} }, // toggle tiled/floating for focused window
    { MODKEY|ShiftMask,             XK_y,          togglefakefullscreen,   {0} }, // toggle "fake" fullscreen
    { MODKEY,                       XK_0,          view,                   {.ui = ~0 } }, // view all tags on current monitor
    { MODKEY,                       XK_comma,      focusmon,               {.i = -1 } }, // focus on previous monitor
    { MODKEY,                       XK_period,     focusmon,               {.i = +1 } }, // focus on next monitor
    { MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } }, // move tags to previous monitor
    { MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } }, // move tags to next monitor
    TAGKEYS(                        XK_1,                                  0) // tags
    TAGKEYS(                        XK_2,                                  1) // tags
    TAGKEYS(                        XK_3,                                  2) // tags
    TAGKEYS(                        XK_4,                                  3) // tags
    TAGKEYS(                        XK_5,                                  4) // tags
    { MODKEY|ShiftMask,             XK_q,          quit,                   {0} }, // quit dwm
    { MODKEY|ControlMask|ShiftMask, XK_r,          spawn,                  SHCMD("systemctl reboot")}, // reboot system
    { MODKEY|ControlMask|ShiftMask, XK_s,          spawn,                  SHCMD("systemctl suspend")}, // suspend system
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 2} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkClientWin,         MODKEY,         Button4,        spawn,          SHCMD("amixer sset Master 5%+ unmute") },
        { ClkClientWin,         MODKEY,         Button5,        spawn,          SHCMD("amixer sset Master 5%- unmute") },
};
