#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/in.h>
#include <linux/string.h>


// this module is used to filter domain name from dns query
// and drop the dns query if the domain name is in the filter list
// used to block some website by domain name

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ouriel, Alexander");
MODULE_DESCRIPTION("dns filter project");

static const char * blocked_domain[]={
    "www.baidu.com",
    "www.google.com",
    "www.sina.com.cn",
    "www.qq.com",
    "www.taobao.com",
    "www.163.com"
};

static const int blocked_domain_num = 6;

struct dns_header {
    __be16 id;
    __be16 flags;
    __be16 qdcount;
    __be16 ancount;
    __be16 nscount;
    __be16 arcount;
};





static unsigned int hook_dns_filter(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    struct iphdr *ip_header = (struct iphdr *)skb_network_header(skb);
    struct udphdr *udp_header;
    struct dns_header *dns_header;
    unsigned int data_len;
    unsigned int payload_len;

    if (ip_header->protocol != IPPROTO_UDP) {
        return NF_ACCEPT;
    }

    udp_header = (struct udphdr *)skb_transport_header(skb);
    if (udp_header->dest != htons(53)) {
        return NF_ACCEPT;
    }

    data_len = ntohs(udp_header->len) - sizeof(struct udphdr);
    if (data_len < sizeof(struct dns_header)) {
        return NF_ACCEPT;
    }

    dns_header = (struct dns_header *)(skb_transport_header(skb) + sizeof(struct udphdr));
    printk(KERN_INFO "get dns packet\n");
    payload_len = data_len - sizeof(struct dns_header);

    if (dns_header->qdcount != htons(1)) {
        return NF_ACCEPT;
    }
    char *domain_name;
    // until now, we get the dns query packet and extract the dns header
    // now we need to extract the domain name from the dns query packet

    // TODO: extract domain name from dns query packet
    // TODO: compare the domain name with the filter list



    return NF_ACCEPT;

}

static struct nf_hook_ops dns_filter_struct = {
    .hook = hook_dns_filter,
    .hooknum = NF_INET_PRE_ROUTING, // Intercept packets just before they are routed (hook type 1)
    .pf = PF_INET, // IPv4 packets
    .priority = NF_IP_PRI_FIRST, // Highest priority
};






static int __init packet_monitor_init(void) {
	nf_register_net_hook(&init_net, &dns_filter_struct);
  
    printk(KERN_INFO "Dns Filter module loaded\n");
    return 0;
}

static void __exit packet_monitor_exit(void) {
	nf_unregister_net_hook(&init_net, &dns_filter_struct);
    printk(KERN_INFO "Dns Filter module unloaded\n");
}

module_init(packet_monitor_init);
module_exit(packet_monitor_exit);








