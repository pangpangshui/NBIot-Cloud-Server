<template>
  <div>
    <nb-manage-header></nb-manage-header>
    <el-main>
      <!--<el-button @click="linkCoapServer">访问coap服务器</el-button>-->
      <el-col v-bind:span="24" class="main">
        <aside v-bind:class="{showSidebar:!isCollapse}">
        <!--<el-radio-group v-model="isCollapse" style="margin-bottom:20px">-->
          <el-button @click.prevent="collapseMenu" type="info" plain>
            <i class="el-icon-more-outline"></i>
          </el-button>
          <!--<el-radio-button v-bind:label="false">展开</el-radio-button>-->
          <!--<el-radio-button v-bind:label="true">收起</el-radio-button>-->
        <!--</el-radio-group>-->

          <!--单个激活 并以 index 作为 path 进行路由跳转-->
        <el-menu default-active="defaultActiveIndex" class="el-menu-vertical-demo" @select="hasSelecte"
                 unique-opened @open="handleOpen" @close="handleClose" v-bind:collapse="isCollapse" router>
          <!--<el-submenu index="1">-->
            <!--<template slot="title">-->
              <!--<i class="el-icon-setting"></i>-->
              <!--<span slot="title" index="1-1">设备管理</span>-->
            <!--</template>-->
              <!--<el-menu-item index="1-1-1">设备列表</el-menu-item>-->
              <!--<el-menu-item index="1-1-2">创建设备</el-menu-item>-->
              <!--<el-menu-item index="1-1-3">预留Item</el-menu-item>-->
          <!--</el-submenu>-->

          <!--<el-submenu index="2">-->
            <!--<template slot="title">-->
              <!--<i class="el-icon-menu"></i>-->
              <!--<span slot="title" index="2-1">在线编程</span>-->
            <!--</template>-->
              <!--<el-menu-item index="2-1-1">我的项目</el-menu-item>-->
              <!--<el-menu-item index="2-1-2">共享项目</el-menu-item>-->
              <!--<el-menu-item index="2-1-3">预留Item</el-menu-item>-->
          <!--</el-submenu>-->

          <!--<el-submenu index="3">-->
            <!--<template slot="title">-->
              <!--<i class="el-icon-more"></i>-->
              <!--<span slot="title" index="3-1">用户管理</span>-->
            <!--</template>-->
              <!--<el-menu-item index="3-1-1">修改信息</el-menu-item>-->
              <!--<el-menu-item index="3-1-2">预留</el-menu-item>-->
          <!--</el-submenu>-->
          <!--取出路由的每一项和index，通过判断menushow来决定是否显示菜单-->

          <!--动态路由到子组件-->
          <template v-for="(item, index) in $router.options.routes" v-if="item.menuShow">
            <el-submenu v-if="item.leaf" v-bind:index="index+''">
              <!--菜单进行分组，分组名可以通过title属性直接设定-->
              <!--item.name和item.children.name来配置菜单栏和子菜单栏的名称- -->
              <template slot="title">
                <i v-bind:class="item.iconCls"></i>
                <span slot="title">{{item.name}}</span>
              </template>

              <el-menu-item v-for="term in item.children" v-bind:key="term.path" v-bind:index="term.path" v-if="term.menuShow"
                                    v-bind:class="$route.path == term.path? 'is-active':''">
                <i v-bind:class="term.iconCls"></i>
                <span slot="title">{{term.name}}</span>
              </el-menu-item>
            </el-submenu>

            <el-menu-item v-else-if="item.leaf && item.children && item.children.length" v-bind:index="children[0].path"
                                      v-bind:class="$route.path == item.children[0].path? 'is-activve':''">
              <i v-bind:class="item.iconCls"></i>
              <span slot="title">{{item.children[0].name}}</span>
            </el-menu-item>
          </template>

        </el-menu>
        </aside>

        <section>
          <div class="">
            <el-col>
              <transition name="fade" mode="out-in">
                <router-view></router-view>
              </transition>
            </el-col>
          </div>
        </section>
      </el-col>
    </el-main>
  </div>
</template>

<script>
    import nbManageHeader from "../components/nbManageHeader";
    import axios from 'axios'
    import "./../assets/css/backManagement.css"
    export default {
        name: "back-management",
        data() {
          return {
            isCollapse: false,
            defaultActiveIndex: "0"
          };
        },
        components: {
          'nb-manage-header': nbManageHeader,
        },
        methods: {
          linkCoapServer() {
            axios.post("/coap", {}).then( (response) => {

            })
          },

          handleOpen(key, keypath) {
            console.log(key, keypath);
          },

          handleClose(key, keypath) {
            console.log(key, keypath);
          },

          collapseMenu() {
            this.isCollapse = !this.isCollapse;
            // console.log(this.isCollapse);
          },

          hasSelecte(index) {
            console.log(this.defaultActiveIndex, index);
            this.defaultActiveIndex = index;
            console.log(this.defaultActiveIndex, index);
          }
        }

    }
</script>

<style scoped>

</style>
