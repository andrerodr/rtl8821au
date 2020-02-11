/******************************************************************************
 *
 * Copyright(c) 2007 - 2013 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef __OSDEP_LINUX_SERVICE_H_
#define __OSDEP_LINUX_SERVICE_H_

#include <linux/netdevice.h>
#include <linux/version.h>

#ifdef CONFIG_USB_SUSPEND
#define CONFIG_AUTOSUSPEND	1
#endif

struct __queue {
		struct	list_head list;
		spinlock_t	lock;
};

	typedef	int	_OS_STATUS;


__inline static struct list_head	*get_list_head(struct __queue	*queue)
{
	return (&(queue->list));
}

#define RTW_TIMER_HDL_ARGS void *FunctionContext

struct _timer_list {
       struct timer_list t;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0)
       void (*function)(unsigned long);
       unsigned long data;
#endif
};

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0))
static void legacy_timer(struct timer_list *t)
{
       struct _timer_list *lt = from_timer(lt, t, t);

       lt->function(lt->data);
}
#endif

__inline static void _init_timer(struct _timer_list *ptimer, void *pfunc,void* cntx)
{
	struct timer_list *t = &ptimer->t;

	//setup_timer(ptimer, pfunc,(u32)cntx);
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 15, 0)
       ptimer->data = (unsigned long)cntx;
       ptimer->function = pfunc;
       timer_setup(t, legacy_timer, 0);
#else
	t->function = pfunc;
	t->data = (unsigned long)cntx;
	init_timer(t);
#endif
}

__inline static void _set_timer(struct _timer_list *ptimer,u32 delay_time)
{
	struct timer_list *t = &ptimer->t;

	mod_timer(t , (jiffies+(delay_time*HZ/1000)));
}

__inline static unsigned char _del_timer_sync(struct _timer_list *ptimer)
{
	struct timer_list *t = &ptimer->t;

	return del_timer_sync(t);
}

__inline static unsigned char del_timer_sync_ex(struct _timer_list *ptimer)
{
	struct timer_list *t = &ptimer->t;

	return del_timer_sync(t);
}
static inline int rtw_netif_queue_stopped(struct net_device *ndev)
{
	return (netif_tx_queue_stopped(netdev_get_tx_queue(ndev, 0)) &&
		netif_tx_queue_stopped(netdev_get_tx_queue(ndev, 1)) &&
		netif_tx_queue_stopped(netdev_get_tx_queue(ndev, 2)) &&
		netif_tx_queue_stopped(netdev_get_tx_queue(ndev, 3)) );
}

// limitation of path length
#define PATH_LENGTH_MAX PATH_MAX

#define NDEV_FMT "%s"
#define NDEV_ARG(ndev) ndev->name
#define ADPT_FMT "%s"
#define ADPT_ARG(rtlpriv) rtlpriv->ndev->name
#define FUNC_NDEV_FMT "%s(%s)"
#define FUNC_NDEV_ARG(ndev) __func__, ndev->name
#define FUNC_ADPT_FMT "%s(%s)"
#define FUNC_ADPT_ARG(rtlpriv) __func__, rtlpriv->ndev->name

#endif

