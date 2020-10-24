void
attachx(Client *c)
{
	Client *at;
	unsigned int n;
	unsigned int attachmode
		= c->flags & AttachMaster
		? AttachMaster
		: c->flags & AttachAbove
		? AttachAbove
		: c->flags & AttachAside
		? AttachAside
		: c->flags & AttachBelow
		? AttachBelow
		: c->flags & AttachBottom
		? AttachBottom
		: attachdefault;

	if (attachmode == AttachAbove) {
		if (!(c->mon->sel == NULL || c->mon->sel == c->mon->clients || ISFLOATING(c->mon->sel))) {
			for (at = c->mon->clients; at->next != c->mon->sel; at = at->next);
			c->next = at->next;
			at->next = c;
			return;
		}
	} else if (attachmode == AttachAside) {
		for (at = c->mon->clients, n = 0; at; at = at->next)
			if (!ISFLOATING(at) && ISVISIBLEONTAG(at, c->tags))
				if (++n >= c->mon->nmaster)
					break;

		if (at && c->mon->nmaster) {
			c->next = at->next;
			at->next = c;
			return;
		}
	} else if (attachmode == AttachBelow) {
		if (!(c->mon->sel == NULL || c->mon->sel == c || ISFLOATING(c->mon->sel))) {
			c->next = c->mon->sel->next;
			c->mon->sel->next = c;
			return;
		}
	} else if (attachmode == AttachBottom) {
		for (at = c->mon->clients; at && at->next; at = at->next);
		if (at) {
			at->next = c;
			c->next = NULL;
			return;
		}
	}
	attach(c); // master (default)
}