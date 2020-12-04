#include "Server.h"
#include "../Packet.h"

#include <iostream>
#include <functional>

namespace project::network
{
    Server::Server()
        : m_connections{},
          m_coordinator{&m_connections, std::bind(this->Send, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)}
    {
        address.host = ENET_HOST_ANY;
        address.port = 1234;
        host = enet_host_create(&address, nc::net::MaxClients, nc::net::ChannelLimit, 0, 0);
        if(!host)
        {
            throw std::runtime_error("Failed to create host");
        }
    }

    Server::~Server()
    {
        enet_host_destroy(host);
    }

    void Server::Poll(uint32_t timeout)
    {
        ENetEvent event;
        while(enet_host_service(host, &event, timeout) > 0)
        {
            switch(event.type)
            {
                case ENET_EVENT_TYPE_RECEIVE:
                {
                    m_coordinator.Dispatch(&event);
                    enet_packet_destroy(event.packet);
                    break;
                }
                case ENET_EVENT_TYPE_CONNECT:
                {
                    OnEventConnect(&event);
                    break;
                }
                case ENET_EVENT_TYPE_DISCONNECT:
                {
                    OnEventDisconnect(&event);
                    break;
                }
                case ENET_EVENT_TYPE_NONE:
                {
                    break;
                }
            }
        }
    }

    void Server::Send(const nc::net::PacketBuffer& data, nc::net::Channel channel, ENetPeer* peer)
    {
        if(!peer)
        {
            ENetPacket* packet = enet_packet_create(data.data, data.size, ENET_PACKET_FLAG_RELIABLE);
            enet_host_broadcast(host, (enet_uint8)channel, packet);
            return;
        }

        ENetPacket* packet = enet_packet_create(data.data, data.size, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, (enet_uint8)channel, packet);
    }

    void Server::OnEventConnect(ENetEvent* event)
    {
        std::cout << "Server::OnEventConnect()\n"
                  << "    Host: " << event->peer->address.host << '\n'
                  << "    Port: " << event->peer->address.port << '\n';

        m_connections.NewConnectionRequest(event->peer);
    }

    void Server::OnEventDisconnect(ENetEvent* event)
    {
        std::cout << "Server::OnEventDisconnect()\n"
                  << "    Host: " << event->peer->address.host << '\n'
                  << "    Port: " << event->peer->address.port << '\n';
    }
}