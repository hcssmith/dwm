/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx = 0;  /* border pixel of windows */
static const unsigned int gappx = 20;    /* gaps between windows */
static const unsigned int barpadv = 20;  /* bar vertical padding (from top)*/
static const unsigned int barpadh = 20;  /* bar vertical padding (from top)*/
static const unsigned int barheight = 2; /* bar vertical padding (from top)*/
static const unsigned int barborder = 0; /* bar vertical padding (from top)*/
static const unsigned int floatbar =
    1; /* 0 means bar won't float; float or dock the bar */
static const unsigned int snap = 32; /* snap pixel */
static const int showbar = 1;        /* 0 means no bar */
static const int topbar = 1;         /* 0 means bottom bar */
static const char *fonts[] = {
    "SauceCodePro Nerd Font:size=10:antialias=true:autohint=true"};
static const char dmenufont[] =
    "SauceCodePro Nerd Font:size=10:antialias=true:autohint=true";
static const char col_gray1[] = "#232136"; /* base */
static const char col_gray2[] = "#2a273f"; /* surface */
static const char col_gray3[] = "#908caa"; /* subtle */
static const char col_gray4[] = "#e0def4"; /* text */
static const char col_cyan[] = "#3e8fb0";  /* pine */
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {"#e0def4", col_cyan, col_cyan},
    [SchemeBar] = {NULL, NULL, col_cyan},
};

/* tagging */
static const char *tags[] = {"",  "",  "",  "", "󰀫",
                             "󰂡", "󱃮", "󰇂", "󱃠"};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class                  instance    title       tags mask isfloating
       monitor */
    {"org.mozilla.firefox", NULL, NULL, 1 << 0, 0, -1},
    {NULL, "vivaldi-stable", NULL, 1 << 0, 0, -1},
    {"chatgpt.com", NULL, NULL, 0, 0, -1},
    {"nvim-project", NULL, NULL, 1 << 1, 0, -1},
    {"st-256color", NULL, NULL, 1 << 2, 0, -1},
    {"cantata", NULL, NULL, 1 << 3, 0, -1},
};

/* layout(s) */
static const float mfact = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;   /* number of clients in master area */
static const int resizehints =
    0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen =
    1; /* 1 will force focus on the fullscreen window */
static const int refreshrate =
    120; /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[]=", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
static char dmenumon[2] =
    "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *applauncher[] = {"app-launcher.sh", "-m",  dmenumon,  "-fn",
                                    dmenufont,         "-nb", col_gray1, "-nf",
                                    col_gray3,         "-sb", col_cyan,  "-sf",
                                    col_gray4,         NULL};
static const char *systemcmd[] = {
    "system.sh", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *wificmd[] = {
    "wifi.sh", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",     col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *srccmd[] = {"src-projects.sh", "-m",  dmenumon,  "-fn",
                               dmenufont,         "-nb", col_gray1, "-nf",
                               col_gray3,         "-sb", col_cyan,  "-sf",
                               col_gray4,         NULL};
static const char *browsercmd[] = {"surf-open.sh", "https://ddg.gg/", NULL};
static const char *termcmd[] = {"st", NULL};
static const char *wallpaper[] = {"wallpaper.sh", NULL};
static const char *volup[] = {"amixer", "sset", "Master", "5%+", NULL};
static const char *voltog[] = {"amixer", "sset", "Master", "toggle", NULL};
static const char *voldown[] = {"amixer", "sset", "Master", "5%-", NULL};
static const char *lightdown[] = {"light", "-U", "5", NULL};
static const char *lightup[] = {"light", "-A", "5", NULL};

static const Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY, XK_p, spawn, {.v = applauncher}},
    {MODKEY | ShiftMask, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_r, spawn, {.v = wallpaper}},
    {MODKEY, XK_q, spawn, {.v = systemcmd}},
    {MODKEY, XK_w, spawn, {.v = wificmd}},
    {MODKEY, XK_b, spawn, {.v = browsercmd}},
    {MODKEY, XK_s, spawn, {.v = srccmd}},
    {0, XF86XK_AudioLowerVolume, spawn, {.v = voldown}},
    {0, XF86XK_AudioRaiseVolume, spawn, {.v = volup}},
    {0, XF86XK_AudioMute, spawn, {.v = voltog}},
    {0, XF86XK_MonBrightnessUp, spawn, {.v = lightup}},
    {0, XF86XK_MonBrightnessDown, spawn, {.v = lightdown}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY | ShiftMask, XK_c, killclient, {0}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8)};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
