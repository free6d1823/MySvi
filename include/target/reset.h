#ifndef _RESET_H
#define _RESET_H

/**
 * struct reset_ctl_bulk - A handle to (allowing control of) a bulk of reset
 * signals.
 *
 * Clients provide storage for the reset control bulk. The content of the
 * structure is managed solely by the reset API. A reset control bulk struct is
 * initialized by "get"ing the reset control bulk struct.
 * The reset control bulk struct is passed to all other bulk reset APIs to apply
 * the API to all the reset signals in the bulk struct.
 *
 * @resets: An array of reset signal handles handles.
 * @count: The number of reset signal handles in the reset array.
 */
struct reset_ctl_bulk {
	struct reset_ctl *resets;
	unsigned int count;
};

#endif
