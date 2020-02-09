# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboutrol <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/07 10:04:52 by roliveir          #+#    #+#              #
#    Updated: 2019/11/16 13:44:26 by roliveir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIDAR_PATH = ./srcs/

LIDAR =		lidar_fct.c	\
		lidar_finder.c	\
		lidar_reader.c	\
		lidar_premade.c	\
		gl.c		\
		gl_display.c	\
		gl_form.c	\
		flag.c		\
		robot_start.c	\
		edge_shift.c	\
		pile.c		\
		mini_lib.c


LIDAR_SRCS = $(addprefix $(LIDAR_PATH),$(LIDAR))
SRCS += $(LIDAR_SRCS)
