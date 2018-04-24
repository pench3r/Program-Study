## screenshot

Index:
![image1](https://github.com/pench3r/Program-Study/blob/master/ruby/demoblog/image1.png)

Post:
![image2](https://github.com/pench3r/Program-Study/blob/master/ruby/demoblog/image2.png)

# 细节

install rvm ruby rails

Gemfile:

	gem 'better_errors'
	gem 'simple_form'
	gem 'bulma-rails'

www.rubygems.org搜索

配置css

	mv app/assets/stylesheets/application.css app/assets/stylesheets/application.scss

application.scss:

	@import "bulma";

Controller:

	rails g controller posts							# 最好都带上s
	rails g controller comments

	rails d controller posts

model:

	rails g model Post title:string content:text		# 创建的表自带s eg:posts, comments

	rails g model Comment name:string comment:text

	rails g migration addColumn

		add_column :comments(table), :post_id(column), :integer

	rails db:migrate

controller/posts_controller.rb
	
	before_action :find_post, only: [:show, :update, :edit, :destory]

	def index
	@posts = Post.all		#  获取所有Post

	def find_post
		@post = Post.find(params[:id])
	end

	private
		def post_param
			params.require(:post).permit(:title, :content)		# 只允许接受参数title, content

	

posts/index.html.erb

	<% content_for :page_title, 'Blog Index' %>		# 通过传递page_title，显示各自的title
	<section class="section">
		<div class="container">
			<% @posts.each do |post| %>
			<div class="card">
				<div class="card-content">
					<div class="media">
						<div class="media-content">
						<div class="content">

posts/show.index.erb

	<%= render @post.comments %>	对应路由为 post_comments  为comments#index template是comments/_comment
	redirect_to post_path(@post)	对应路由为 post /posts/:id(.:format)  为post#show
	<%= render 'comments/form' %>	识别为 app/views/comments/_form.html.erb

comments/_form.html.erb

	<%= simple_form_for([@post, @post.comments.build]) do |f| %>

	@post 是posts controller传递的object对象， 而后使用@post.comments.build依据post_id创建一个空的comments对象

	@post.comments.build 对应 Comment id: nil, name: nil, comment: nil, post_id: 8, created_at: nil, updated_at: nil

	
	总结，simple_for_for 接受的参数为model，这样可以传递出去，就是字段值， 对应的路由为comments#create

layouts/application.html.erb

	...
	<%= yield :page_title %>

posts/new.html.erb

	<section class=section">
		<div class="container">
		<%= simple_form_for @post do |f| %>
		<div class="field">
			<div class="control">
				<%= f.input :title, input_html: {class: 'input is-info'}, wrapper: false, label_html: {class: 'label'} %>
				<%= f.button :submit, 'Create new post', class: 'button is-primary' %>

路径的判断，通过rails routes

	posts_path (index)
	edit_post_path(@post)  (edit)

routes:

	resources :posts do				# 注册posts control的所有路由
		resources :comments			# 在comments是所有路由前添加上了posts的路由
	end

数据表连接

	post.comments  == select comments.* from comments where comments.post_id

	post has_many comments

CSS:

- 各种标签： section  article   
- class属性： card card-content  media media-content  


BOOTSTRAP:

	<div class="media">
		<div class="media-content">
		<table class="table table-hover">
			<thead>
			<tbody>
