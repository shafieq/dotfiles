/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int gappx     = 14;       /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Monospace Bold:size=12" };
static const char dmenufont[]       = "Monospace:size=13";
static const char col_gray1[]       = "#bcbcbc";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#000000";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define XF86MonBrightnessDown           0x1008ff03
#define XF86MonBrightnessUp             0x1008ff02
#define XF86AudioMute                   0x1008ff12
#define XF86AudioLowerVolume            0x1008ff11
#define XF86AudioRaiseVolume            0x1008ff13
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *brightup[]  = { "xbacklight", "+15", NULL};
static const char *brightdown[]  = { "xbacklight", "-15", NULL};
static const char *dmenuunicode[] = { "dmenuunicode", NULL };
static const char *musicnext[]  = { "mpc", "next", NULL};
static const char *musicprev[]  = { "mpc", "prev", NULL};
static const char *musictoggle[] = { "mpc", "toggle", NULL};
static const char *chromium[] = { "chromium", NULL };
static const char *neomutt[] = { "st", "neomutt", NULL };
static const char *newsboat[] = { "st", "newsboat", NULL };
static const char *music[] = { "st", "ncmpcpp", NULL };
static const char *vifm[] = { "st","vifm", NULL };
static const char *volumeup[]  = { "amixer", "-q", "set", "Master","5%+","unmute", NULL };
static const char *volumedown[]  = { "amixer", "-q", "set", "Master","5%-","unmute", NULL };
static const char *volumemute[]  = { "amixer", "-q", "set", "Master","toggle", NULL };
static const char *screenshot[] = { "flameshot","gui","-p","/tmp", NULL };
static const char *poweroff[] = { "sudo","shutdown","-h", "now",NULL };
static const char *reboot[] = { "sudo","shutdown","-r", "now",NULL };
static const char *slock[] = { "slock",NULL };
static const char *clipboard[] = { "showclip",NULL };

static Key keys[] = {
        /* modifier                     key        function        argument */
        { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
        { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
        { MODKEY,                       XK_b,      togglebar,      {0} },
        { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
        { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
        { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
        { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
        { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
        { MODKEY,                       XK_Tab,    view,           {0} },
        { MODKEY,	                XK_c,      killclient,     {0} },
        { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
        { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
        { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
        { MODKEY,                       XK_space,  setlayout,      {0} },
        { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
        { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
        { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
        { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
        { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
        { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
        { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        TAGKEYS(                        XK_1,                      0)
        TAGKEYS(                        XK_2,                      1)
        TAGKEYS(                        XK_3,                      2)
        TAGKEYS(                        XK_4,                      3)
        TAGKEYS(                        XK_5,                      4)
        TAGKEYS(                        XK_6,                      5)
        TAGKEYS(                        XK_7,                      6)
        TAGKEYS(                        XK_8,                      7)
        TAGKEYS(                        XK_9,                      8)
        //MediaKeys
        { 0,                            XF86MonBrightnessUp,       spawn,       {.v = brightup } },
        { 0,                            XF86MonBrightnessDown,     spawn,       {.v = brightdown } },
        { 0,                            XF86AudioRaiseVolume,      spawn,       {.v = volumeup } },
        { 0,                            XF86AudioLowerVolume,      spawn,       {.v = volumedown } },
        { 0,                            XF86AudioMute,             spawn,       {.v = volumemute } },
        //Others
        { MODKEY,                       XK_backslash,              spawn,       {.v = musictoggle } },
        { MODKEY,                       XK_semicolon,              spawn,       {.v = musicprev } },
        { MODKEY,                       XK_apostrophe,             spawn,       {.v = musicnext } },
        { MODKEY,                       XK_F2,                     quit,        {0} },
        { MODKEY,                       XK_grave,                  spawn,       {.v = dmenuunicode } },
        { MODKEY|ShiftMask,             XK_w,                      spawn,       {.v = chromium } },
        { MODKEY|ShiftMask,             XK_m,                      spawn,       {.v = music } },
        { MODKEY,                       XK_n,                      spawn,       {.v = newsboat } },
        { MODKEY,                       XK_e,                      spawn,       {.v = neomutt } },
        { MODKEY,                       XK_v,                      spawn,       {.v = vifm } },
	{ MODKEY|ShiftMask,             XK_x,              	   spawn,       {.v = poweroff } },
	{ MODKEY|ShiftMask,             XK_BackSpace,              spawn,       {.v = reboot } },
	{ MODKEY,                       XK_x,                      spawn,       {.v = slock } },
	{ MODKEY,                       XK_Insert,                 spawn,       {.v = clipboard } },
	{ 0,                            XK_Print,  		   spawn,       {.v = screenshot } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
